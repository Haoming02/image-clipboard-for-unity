using System;
using System.Runtime.InteropServices;
using UnityEngine;

public static class ImageClipboard
{
    [DllImport("ImageClipboard.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void PasteImage(out int imageSize, out IntPtr imageData);

    public static bool Paste(ref Texture2D _texture)
    {
        PasteImage(out int size, out IntPtr arrayPtr);

        if (size < 0)
            return false;

        byte[] array = new byte[size];
        Marshal.Copy(arrayPtr, array, 0, size);
        Marshal.FreeHGlobal(arrayPtr);

        _texture.LoadImage(array);
        _texture.Apply();
        return true;
    }
}
