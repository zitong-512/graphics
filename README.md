# Raymarched sphere

A minimal, dependency-free C++17 ray marcher based on the organization of the
neighboring graphics-course projects. Rays advance through a signed distance
field until they reach the sphere surface. It supports normal and ambient
shading; the shader used for the image is selected in `main.cpp`.

The pinhole camera uses explicit viewport width and height values, with the
viewport placed one unit in front of the camera.

## Build and run

```powershell
cmake -S . -B build
cmake --build build
.\build\Debug\main.exe
```

For a single-config generator, the executable may instead be directly under
`build`.

The pixel loop in `main.cpp` calls `Raymarching::color()` once per camera ray
and writes a binary RGB PPM (`P6`) named `image.ppm`.
