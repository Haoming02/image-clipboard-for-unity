#include "pch.h"
#include "clip.h"
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

static Mat paste(HWND hWnd) {
  Mat mat;

  if (!OpenClipboard(hWnd))
    return mat;

  HBITMAP hbitmap = nullptr;

  if (IsClipboardFormatAvailable(CF_BITMAP))
    hbitmap = (HBITMAP)GetClipboardData(CF_BITMAP);

  else if (IsClipboardFormatAvailable(CF_DIB)) {
    HANDLE handle = GetClipboardData(CF_DIB);
    LPVOID hmem = GlobalLock(handle);

    if (hmem) {
      BITMAPINFO *bmpinfo = (BITMAPINFO *)hmem;
      int offset = 0;
      if (bmpinfo->bmiHeader.biBitCount <= 8)
        offset = sizeof(RGBQUAD) * (1 << bmpinfo->bmiHeader.biBitCount);

      BYTE *bits = (BYTE *)(bmpinfo) + bmpinfo->bmiHeader.biSize + offset;
      hbitmap = CreateDIBitmap(GetDC(hWnd), &bmpinfo->bmiHeader, CBM_INIT, bits,
                               bmpinfo, DIB_RGB_COLORS);

      GlobalUnlock(hmem);
    }
  }

  ReleaseDC(hWnd, GetDC(hWnd));

  if (hbitmap) {
    BITMAP bm;
    GetObject(hbitmap, sizeof(bm), &bm);

    int cx = bm.bmWidth;
    int cy = bm.bmHeight;

    if (bm.bmBitsPixel == 32) {
      mat.create(cy, cx, CV_8UC4);
      BITMAPINFOHEADER bi = {sizeof(bi), cx, -cy, 1, 32, BI_RGB};
      GetDIBits(GetDC(hWnd), hbitmap, 0, cy, mat.data, (BITMAPINFO *)&bi,
                DIB_RGB_COLORS);
    }
  }

  CloseClipboard();
  return mat;
}

void PasteImage(int *imageSize, unsigned char **imageData) {
  HWND hWnd = GetForegroundWindow();
  Mat image = paste(hWnd);

  if (image.empty()) {
    *imageSize = -1;
    imageData = nullptr;
    return;
  }

  vector<unsigned char> buffer;
  imencode(".jpg", image, buffer);

  *imageSize = buffer.size();
  *imageData = new unsigned char[*imageSize];

  memcpy(*imageData, buffer.data(), *imageSize);
}
