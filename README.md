# 实现

-x/y轴无限地图

-方块的破环/放置

-基础物品栏

-基础角色动画

# 环境

-C++ 17

-CMake 3.12

# 库

所有库均为源代码编译

没有指定路径为默认文件结构

External/FastNoiseLite/FastNoiseLite.h

External/glad

External/GLFW

External/glm

External/nlohmann

External/stb/stb_image.h

External/stb/stb_image.cpp

External/stb/stb_truetype.h

External/stb/stb_truetype.cpp

# 贴图

需要原版Minecraft游戏资源

路径:游戏.jar\assets\minecraft\textures

将textures文件夹复制到Assets文件夹中

贴图版本为1.8 - 1.12.2

# 构建

cmake -B build

cmake --build build
