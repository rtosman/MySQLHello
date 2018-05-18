-- premake5.lua
workspace "TemplateTreesDemo"
   configurations { "Debug", "Release" }

project "HelloMySQL"
   kind "ConsoleApp"
   language "C++"
   toolset "clang"
   buildoptions { "-std=c++17" }
   targetdir "bin/%{cfg.buildcfg}"

   includedirs { "/usr/local/mysql/include/" }
   libdirs { "/usr/local/mysql-5.7.22-macos10.13-x86_64/lib/" }
   
   links { 
         "mysqlclient",
         "z",
         "m",
         "ssl",
         "crypto"
   }
   
   files { "**.h", "*.hpp", "**.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On" 
