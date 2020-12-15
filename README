# OCR

![epita]()
![S3]()
![C]()
![C version]()

Our OCR is a text recognition tool developped for the EPITA's 3rd semester
project.

This software allows to extract text from an image, through 3 processes:

- [x] A binarization of the image.

- [x] A segmentation to analyse each character independtly.

- [x] A recognition of each character through a neural network.

# Getting Started

These instructions will allow you to get a copy of this project and set it up
on your machine.

## Prerequisites

- [SDL 2]()

- [GTK 3]()

- [JSON-C]()

## Installing

- Download the project from github

```
$ git clone https://github.com/yvalmor/OCR.git
```

- Go in the created folder and make

```
$ cd OCR
$ make
```

- An ocr executable should be created in the bin folder, go in this folder and
  execute it.

```
$ cd bin
$ ./ocr
```

## Running

Once launched, the software will show you an UI. That UI is composed of two
main parts: an analysis part, and a training part.

The analysis part is made to extract text from an image whereas the training
part is made to train the neural network.

## Debugging

Our software can take an additional parameter.

- `--debug` (or `-d`): if specified, the code will save the different steps the
  image goes through (rotation, segmentation, border removing and segmentation)
  in the bin folder and prompt the results of the training of the network in
  the console.

```
$ ./ocr -d
```

# Credits

This project was developped by `Eliott Beguet`, `Nael Valin`, `Souleymane
Sentici` and `Yvon Morice`.
