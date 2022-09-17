# H5+ : Heroes 5 extended with C++ 

Setup steps:
1. Install [Git](https://git-scm.com/).
3. Install [Visual Studio](https://visualstudio.microsoft.com/).
2. Install [VCPKG](https://vcpkg.io/en/index.html).
4. Open your favorite IDE (Visual Studio / Visual Studio Code / etc).
5. [Set CMAKE_TOOLCHAIN_FILE to VCPKG](https://vcpkg.io/en/docs/users/buildsystems/cmake-integration.html).
6. Move Heroes5x.exe to your Tote/bin.
7. Build the project.
8. Move all .dll files from build/Debug to Tote/bin.
9. Rename Tote/bin/H5x.dll to Tote/bin/UbiStats.dll.

Finally, run ToTe/bin/Heroes5x.exe.

(Tote = Tribes of the East)