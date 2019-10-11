#include "tagprovider.h"
#include <algorithm>
#include <string_view>
#include <regex>
#include <string>
#include <exception>
#include <errno.h>
#include <sys/xattr.h>
#include <QVariant>
#include "Plist.hpp"

namespace  {
    constexpr std::string_view tagsAttrName = "com.apple.metadata:_kMDItemUserTags";

    const std::vector<std::string> colors = {
        "",
        "Grey",
        "Green",
        "Purple",
        "Blue",
        "Yellow",
        "Red",
        "Orange"
    };

    struct TagInfo {
        explicit TagInfo(const std::string &desc) {
            std::regex r("(\\w+)\n(\\d)");
            std::smatch match;
            if (std::regex_match(desc, match, r)) {
                name = match.str(1);
                color = std::stoi(match.str(2));
            } else {
                throw std::runtime_error("bad tag string");
            }
        }

        explicit TagInfo(int color) :
            name(color < 8 ? colors[color] : ""),
            color(color)
        {
        }

        std::string toString() const {
            return name + "\n" + std::to_string(color);
        }

        std::string name;
        int color;
    };

    std::vector<TagInfo> parseTagsPlist(const std::vector<char> &data) {
        std::vector<boost::any> root;
        Plist::readPlist(data.data(), static_cast<int64_t>(data.size()), root);
        std::vector<TagInfo> result;
        for (auto s: root) {
            result.emplace_back(boost::any_cast<std::string>(s));
        }
        return result;
    }

    std::vector<char> createTagsPlist(const std::vector<TagInfo> &tags) {
        std::vector<boost::any> root;
        for (auto t: tags) {
            root.push_back(t.toString());
        }
        std::vector<char> result;
        Plist::writePlistBinary(result, root);
        return result;
    }

    std::vector<TagInfo> loadTagsForFile(const std::string &filename) {
        std::vector<char> data(4096, 0);
        ssize_t r = getxattr(filename.c_str(), tagsAttrName.data(), data.data(), data.size(), 0, 0);
        if (r == -1) {
            if (errno == ENOATTR || errno == ENOTSUP || errno == EPERM || errno == EACCES || errno == EINVAL || errno == ENOENT) {
                return {};
            } else {
                throw std::runtime_error(strerror(errno));
            }
        } else if (r == 0) {
            return {};
        } else {
            data.resize(static_cast<size_t>(r));
            return parseTagsPlist(data);
        }
    }

    void saveTagsForFile(const std::string &filename, const std::vector<TagInfo> &tags) {
        std::vector<char> data = createTagsPlist(tags);
        int r = setxattr(filename.c_str(), tagsAttrName.data(), data.data(), data.size(), 0, 0);
        if (r == -1) {
            switch (errno) {
            case ENOTSUP:
            case EPERM:
            case EACCES:
                return;
            default:
                throw std::runtime_error(strerror(errno));
            }
        } else {
            return;
        }
    }
}

struct TagProvider::Impl {
    QUrl url;
    std::vector<TagInfo> tags;
};

TagProvider::TagProvider(QObject *parent):
    QObject(parent),
    impl(new Impl)
{
}

TagProvider::~TagProvider() {

}

QUrl TagProvider::getUrl() const
{
    return impl->url;
}

void TagProvider::setUrl(const QUrl &url)
{
    impl->tags = loadTagsForFile(url.path().toStdString());
    impl->url = url;
    emit urlChanged();
    emit tagsChanged();
}

QVariantList TagProvider::getTags() const
{
    QVariantList result;
    for (auto ti: impl->tags) {
        if (ti.color > 0 && ti.color < 8) {
            result.append(QVariant(ti.color));
        }
    }
    return result;
}

void TagProvider::toggleTag(int tag)
{
    auto it = std::find_if(impl->tags.begin(), impl->tags.end(), [tag](const TagInfo &ti) {
        return ti.color == tag;
    });
    if (it == impl->tags.end()) {
        impl->tags.push_back(TagInfo(tag));
    } else {
        impl->tags.erase(it);
    }
    saveTagsForFile(impl->url.path().toStdString(), impl->tags);
    emit(tagsChanged());
}

