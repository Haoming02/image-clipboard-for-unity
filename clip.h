#pragma once

#ifdef CLIP_EXPORTS
#define CLIP_API __declspec(dllexport)
#else
#define CLIP_API __declspec(dllimport)
#endif

extern "C" CLIP_API void PasteImage(int *imageSize, unsigned char **imageData);
