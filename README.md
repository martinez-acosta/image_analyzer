# Image Analyzer
![Last Commit](https://img.shields.io/github/last-commit/martinez-acosta/image_analyzer)

## Project Goals


Develop an application that implements image analysis algorithms such as grayscale, histogram, convolution operations with user input kernel, and Watershed

## Libraries/Languages

- Qt
- C++
- QCustomPlot (to plot the histogram)


## Status

- [x] Convolution (user-entered variable-size kernel)
- [x] Histogram (8-bit depth images)
- [x] Labeling
- [x] Otsu


## Build Setup

```bash
# make the project platform-specific
$ qmake ImageAnalizer.pro

# compile and generate the executable
$ make

# run
$ ./OpenImageAnalysis
```