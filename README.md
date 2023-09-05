# cmake_opencv_fetchcontent

An example of using FetchContent to include OpenCV in your CMake C++ project

 This VS Code project now uses a `launch.json` file, which enables us to define a *sourceFileMap* and step into OpenCV code while debugging. This means you should use the generic VS Code 'F5' Debug keyboard shortcut rather than the 'Ctrl+F5' provided by the CMake Extension.


## Dependencies

- Install Visual Studio Build Tools 2022
  - or Visual Studio Community/Professional/Enterprise 2022
  - E.g. using one of the [Evergreen Bootstrappers](https://learn.microsoft.com/en-us/visualstudio/releases/2022/release-history#evergreen-bootstrappers)
- Install [VS Code](https://code.visualstudio.com)
- Install [CMake](https://cmake.org/install)
- Install the C/C++ Extension Pack in VS Code


## Code/Build/Debug Cycle

- Open this folder in VS Code
- Press 'Ctrl+Shift+P'
- Execute the "CMake: Select a Kit" command
- Select the VS Build Tools 2022 amd64 kit
  - or Visual Studio Community/Professional/Enterprise 2022 amd64 kit
- Now press 'Ctrl+Shift+P' and do "CMake: Configure"
- Then 'Ctrl+Shift+P' and "CMake: Build"
- Press 'Ctrl+P' and open "main.cpp"
- Use F9 to place some breakpoint(s) in `main()`
- Press F5 to debug the example OpenCV program in main.cpp
- Try stepping into some OpenCV code using F11


## OpenCV in the CERN ROOT C++ Interpreter

If you want to use OpenCV from within [ROOT](https://root.cern.ch/) or [cling](https://github.com/root-project/cling), first make sure you uninstall (using the Visual Studio Installer) all Windows Kits (SDKs) except the one that ROOT was built with. At the time of writing, the [latest ROOT release for windows](https://root.cern/download/root_v6.28.06.win32.vc17.exe) was built with Windows SDK 10.0.19041.0.

Once you have built this CMake project you can start ROOT:
```
user@machine MSYS ~/Documents/GitHub/cmake_opencv_fetchcontent (main)
$ /c/root_v6.28.06/bin/root.exe
   ------------------------------------------------------------------
  | Welcome to ROOT 6.28/06                        https://root.cern |
  | (c) 1995-2023, The ROOT Team; conception: R. Brun, F. Rademakers |
  | Built for win64 on Aug 28 2023, 11:29:15                         |
  | From tags/v6-28-06@v6-28-06                                      |
  | With MSVC 19.32.31332.0                                          |
  | Try '.help'/'.?', '.demo', '.license', '.credits', '.quit'/'.q'  |
   ------------------------------------------------------------------
```
Now to get OpenCV into the interpreter:
```
root [] #pragma cling load("build/_deps/opencv-src/build/x64/vc16/bin/opencv_world480.dll")
root [] #pragma cling add_include_path("build/_deps/opencv-src/build/include")
root [] #include <opencv2/core.hpp>
root [] #include <opencv2/imgproc.hpp>
root [] #include <opencv2/highgui.hpp>
root [] using namespace cv;
root [] char wndname[] = "OpenCV Example";
root [] int width = 1024; int height = 768;
root [] Mat image = Mat::zeros(height, width, CV_8UC3);
root [] Size textsize = getTextSize("Hello OpenCV!", FONT_HERSHEY_COMPLEX, 3, 5, 0);
root [] Point org((width - textsize.width)/2, (height - textsize.height)/2);
root [] putText(image, "Hello OpenCV!", org, FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 5, LINE_AA);
root [] imshow(wndname, image);
```
At this point the "Hello, OpenCV!" window should be displayed, but unresponsive. Calling waitKey() enters the OpenCV highgui eventloop.
```
root [] waitKey();
```
Press any key to get out of the event loop and back to ROOT. To get rid of the lingering window:
```
root [] destroyAllWindows();
```
When you're done interpreting C++ code, type '.q'.
```
root [] .q
user@machine MSYS ~/Documents/GitHub/cmake_opencv_fetchcontent (main)
```
