# Text Editor

A text editor specifically designed for LongOS. 

![LongOS-Texteditor](screenshots/LongOS-Texteditor.png)
![Texteditor-2](screenshots/LongOS-Texteditor-2.png)
![Texteditor-3](screenshots/LongOS-Texteditor-3.png)
![Texteditor-4](screenshots/LongOS-Texteditor-4.png)

## Dependencies

### Debian/Ubuntu

```
sudo apt install equivs curl git devscripts lintian build-essential automake autotools-dev --no-install-recommends
```

## Build

```shell
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
make
```

## Install

```shell
sudo make install
```

## License

This project has been licensed by GPLv3.
