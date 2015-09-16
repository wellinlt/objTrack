# objTrack
testando detecção e rastreio de objetos usando opencv e visual studio 2013

<b>Definindo variável do ambiente</b></br>
</br>
setx -m OPENCV_DIR D:\OpenCV\Build\x86\vc10     (suggested for Visual Studio 2010 - 32 bit Windows)</br>
setx -m OPENCV_DIR D:\OpenCV\Build\x64\vc10     (suggested for Visual Studio 2010 - 64 bit Windows)</br>
</br>
</br>
setx -m OPENCV_DIR D:\OpenCV\Build\x86\vc11     (suggested for Visual Studio 2012 - 32 bit Windows)</br>
setx -m OPENCV_DIR D:\OpenCV\Build\x64\vc11     (suggested for Visual Studio 2012 - 64 bit Windows)</br>
</br>
</br>
setx -m OPENCV_DIR D:\OpenCV\Build\x86\vc12     (suggested for Visual Studio 2013 - 32 bit Windows)</br>
setx -m OPENCV_DIR D:\OpenCV\Build\x64\vc12     (suggested for Visual Studio 2013 - 64 bit Windows)</br>

If you built static libraries then you are done. Otherwise, you need to add the bin folders path to the systems path. This is cause you will use the OpenCV library in form of “Dynamic-link libraries” (also known as DLL). Inside these are stored all the algorithms and information the OpenCV library contains. The operating system will load them only on demand, during runtime. However, to do this he needs to know where they are. The systems PATH contains a list of folders where DLLs can be found. Add the OpenCV library path to this and the OS will know where to look if he ever needs the OpenCV binaries. Otherwise, you will need to copy the used DLLs right beside the applications executable file (exe) for the OS to find it, which is highly unpleasent if you work on many projects. To do this start up again the Path Editor and add the following new entry (right click in the application to bring up the menu):</br>
</br>
%OPENCV_DIR%\bin</br>
</br>
Save it to the registry and you are done. If you ever change the location of your build directories or want to try out your applicaton with a different build all you will need to do is to update the OPENCV_DIR variable via the setx command inside a command window.
