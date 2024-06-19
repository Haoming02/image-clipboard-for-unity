# Image Clipboard for Unity
A library that allows you to copy and paste images from **Windows** desktop into UnityEngine

### How to Use
0. Install [OpenCV 4.10.0](https://github.com/opencv/opencv/releases/tag/4.10.0); copy the `opencv_world4100.dll` from `<path to opencv>\build\x64\vc16\bin` to the `Plugins` folder
1. Download the `ImageClipboard.dll` from [Releases](https://github.com/Haoming02/image-clipboard-for-unity/releases); put it in the `Plugins` folder
2. Download the `ImageClipboard.cs` script
3. Call `ImageClipboard.Paste()` to receive the image currently in clipboard
    - If successful, the function returns `true`, otherwise *(**eg.** you copied text instead of image)* it will return `false`

<hr>

- Refer to the [src](https://github.com/Haoming02/image-clipboard-for-unity/tree/src) branch for the source code of the `.dll` library
