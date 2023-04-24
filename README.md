# FFmpeg64bit-Compile-script-And-Makefile-on-Windows
<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="74" height="20" role="img" aria-label="bat: 35.4%"><title>bat: 35.4%</title><linearGradient id="s" x2="0" y2="100%"><stop offset="0" stop-color="#bbb" stop-opacity=".1"/><stop offset="1" stop-opacity=".1"/></linearGradient><clipPath id="r"><rect width="74" height="20" rx="3" fill="#fff"/></clipPath><g clip-path="url(#r)"><rect width="27" height="20" fill="#555"/><rect x="27" width="47" height="20" fill="#e05d44"/><rect width="74" height="20" fill="url(#s)"/></g><g fill="#fff" text-anchor="middle" font-family="Verdana,Geneva,DejaVu Sans,sans-serif" text-rendering="geometricPrecision" font-size="110"><text aria-hidden="true" x="145" y="150" fill="#010101" fill-opacity=".3" transform="scale(.1)" textLength="170">bat</text><text x="145" y="140" transform="scale(.1)" fill="#fff" textLength="170">bat</text><text aria-hidden="true" x="495" y="150" fill="#010101" fill-opacity=".3" transform="scale(.1)" textLength="370">35.4%</text><text x="495" y="140" transform="scale(.1)" fill="#fff" textLength="370">35.4%</text></g></svg>

<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="94" height="20" role="img" aria-label="Makefile: 8.2%"><title>Makefile: 8.2%</title><linearGradient id="s" x2="0" y2="100%"><stop offset="0" stop-color="#bbb" stop-opacity=".1"/><stop offset="1" stop-opacity=".1"/></linearGradient><clipPath id="r"><rect width="94" height="20" rx="3" fill="#fff"/></clipPath><g clip-path="url(#r)"><rect width="55" height="20" fill="#555"/><rect x="55" width="39" height="20" fill="#97ca00"/><rect width="94" height="20" fill="url(#s)"/></g><g fill="#fff" text-anchor="middle" font-family="Verdana,Geneva,DejaVu Sans,sans-serif" text-rendering="geometricPrecision" font-size="110"><text aria-hidden="true" x="285" y="150" fill="#010101" fill-opacity=".3" transform="scale(.1)" textLength="450">Makefile</text><text x="285" y="140" transform="scale(.1)" fill="#fff" textLength="450">Makefile</text><text aria-hidden="true" x="735" y="150" fill="#010101" fill-opacity=".3" transform="scale(.1)" textLength="290">8.2%</text><text x="735" y="140" transform="scale(.1)" fill="#fff" textLength="290">8.2%</text></g></svg>

<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="86" height="20" role="img" aria-label="other: 56.4%"><title>other: 56.4%</title><linearGradient id="s" x2="0" y2="100%"><stop offset="0" stop-color="#bbb" stop-opacity=".1"/><stop offset="1" stop-opacity=".1"/></linearGradient><clipPath id="r"><rect width="86" height="20" rx="3" fill="#fff"/></clipPath><g clip-path="url(#r)"><rect width="39" height="20" fill="#555"/><rect x="39" width="47" height="20" fill="#dfb317"/><rect width="86" height="20" fill="url(#s)"/></g><g fill="#fff" text-anchor="middle" font-family="Verdana,Geneva,DejaVu Sans,sans-serif" text-rendering="geometricPrecision" font-size="110"><text aria-hidden="true" x="205" y="150" fill="#010101" fill-opacity=".3" transform="scale(.1)" textLength="290">other</text><text x="205" y="140" transform="scale(.1)" fill="#fff" textLength="290">other</text><text aria-hidden="true" x="615" y="150" fill="#010101" fill-opacity=".3" transform="scale(.1)" textLength="370">56.4%</text><text x="615" y="140" transform="scale(.1)" fill="#fff" textLength="370">56.4%</text></g></svg>

windows上配置和编译ffmpeg有点麻烦，写一个脚本方便运行

main.c和video.mp4可以用来测试脚本能不能用

## Makefile变量

### CC
编译器，我用的是gcc64位的，ffmpeg也要用64位。注意，要是有人用32位gcc，那ffmpeg也要用32位。

### IncludeDirFlag
表示include文件夹，就是头文件的位置,自己修改好自己对应的位置
一般在...\ffmpeg\include

### LinkDirFlag
动态连接库的位置，一般在...\ffmpeg\bin下，注意ffmpeg需要是shared版本
我脚本中用的是64位ffmpeg和64位的gcc，也可以改g++但是改g++的时候要注意修改FLAG中的-std=c11为-std=c++11

ffmpeg windows：根据自己的编译器选择。
64位下载： https://github.com/BtbN/FFmpeg-Builds/releases
32位下载：https://github.com/sudo-nautilus/FFmpeg-Builds-Win32/releases


### LinkFlag
表示连接那个dll文件，就是-L后面那个文件夹中的。

### FLAG
一些编译设置，可以自己选择


## run.bat
设置变量，或者修改一些东西的时候不要为了美观打空隔，不然有可能会错
比如
set FFMPEG_BIN=D:\Program Files\ffmpeg-shared\bin
改成
set FFMPEG_BIN = D:\Program Files\ffmpeg-shared\bin
就是错的，不可以！！！

### MINGW64_BIN
表示你的Mingw也就是gcc或者g++的位置，make也在这个位置
注意：你的`make`可能是`mingw32-make.exe`，最好在原来的位置复制一份，改名叫make.exe,不然的话就要把run.bat中的`make`改为`mingw32-make`

### FFMPEG_BIN
就是你动态连接库的位置，一般在...\ffmpeg\bin下
和Makefile中LinkDirFlag同一个位置。

## 使用方式
把Makefile和run.bat放在同一个文件夹下，把要编译的main.cpp也放在同一文件夹下
配置好后，直接运行run.bat就可以直接自动编译加运行，如果检查到之前编译过，run.bat会自动清除并，重新编译。运行时同样会自动检测环境中是否含有...\ffmpeg\bin，没有会自动加入。

## 其它注意事项：
run.bat最终运行的是main.exe要是想让他运行其它的就要修改main.exe为其它名字
Makefile中只是把main.cpp编译为main.exe,要是想要复杂功能的需要修改

## 运行效果
直接运行run.bat,run.bat自己会运行make来执行当前文件夹下的Makefile
![runPic](run.png)
绿色框框中就是运行输出。
