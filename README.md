# NanoRender
A review of render pipeline

[2022-8-30 16:43:19]
# Windows Component Display

This part uses WIN32 API for "plotting figures on screen".

Awkward for author to call the WIN32 API by myself, I turn to introduce a segment from another subtle repository [mini3d](https://github.com/skywind3000/mini3d), which actually rendering a box with only hundreds of lines.

With these codes, we can now export the framebuffer definitely to the screen. We can say that the journey rasterizing a triangle is truly 'over'.