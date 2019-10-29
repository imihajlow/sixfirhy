Sixfirhy is a minimal image viewer for macOs allowing placing Finder tags on your pictures.

# Building

Use qmake + make to build:
```bash
    cd some-build-folder
    qmake path-to-source-folder
    make
```
After building use Qt's macdeployqt tool to include Qt frameworks into the app bundle:
```bash
    macdeployqt sixfirhy.app -qmldir=path-to-source-folder
```

# Usage

Key bindings:
    o                   open folder
    right,space         next image
    left,backspace      previous image
    shift+right,
        shift+space     skip 10 images forward
    shift+left,
        shift+backspace skip 10 images backward
    home                first image
    end                 last image
    f                   toggle fit/original size
    t                   toggle tags visible
    o                   open folder
    1-7                 toggle color tags
    s                   toggle image smoothness

# Name

Sixfirhy is a demon in Dungeon Crawl Stone Soup.
> A small vile creature that moves in bursts, stopping then darting with lightning speed. It sprays sparks as it goes.
