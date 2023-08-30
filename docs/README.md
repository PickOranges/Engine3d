# Engine3d
- Graphics Engine for learning purpose. Written in C++ and DirectX11/HLSL. [Click here for source code.](https://github.com/PickOranges/Engine3d/tree/develop_sm)

- The goal of this project is not only to build a 3D rendering engine from scratch, the logic/game loop can be fused into the system later without any refactoring. Many commonly used design patterns for game engine are implemented. Finally some post-processing effects are implemented to test the performance. The FPS of those effects are 90 ~ 135.


## Features
### 1. Message/Event Queue 
To deal with both rendering ticks and gameplay logic ticks.

### 2. Reflection Mechanism 
Loading models without specifying vertex attributes and mesh constants manually. The properties of meshes and effects can be modified by mouse at run-time, the data will be updated and the correct rendering will be done.

### 3. Render Graph 
For resources and passes reuse and management. (In the future the configuration of passes and render graphs may be replaced via lua or json scripts, so that we can modify the rendering setting at run-time, without recompiling the source code.)

### 4. Render Queue System and Multi-pass System 
To batch and defer the commands sending to GPU side, so that the communication between CPU and GPU is reduced, thus the performance will be leveraged. Note although there was a performace improvement, it cannot beat the DX12. DX12 reduced the overhead of higher level design, users can touch more lower level resources. Thus the performance issue will be solved from the root.

### 5. Exception Handling
Exception will be throwed with detailed information, this makes debugging a rendering application much easier.

### 6. Scene Graph and Dirty Flag
Organizes model nodes and meshes with a tree-like structure. The dirty flags can deferred the updates of unchanged models in the scene, this may be a double edged sword though (i.e. when the gameplay logics are included). But for dealing with rendering tasks so far, dirty flag is good.

### 7. Resource Pool
Static resources for reusing among different passes or effects.

### 8. Post-Processing Effects
- Normal Mapping
- Gauss Filter
- Outline Effect via Stencil Buffer

## Sceenshots
![Screenshot (130)](https://user-images.githubusercontent.com/55946962/167479209-ab5b1ccb-15bc-4bc1-ae3d-b36d055f4892.png)

## Dependencies
- ImGui
- Assimp
- DirecXTex
- Win32 API

## References
- Course Games104: https://games104.boomingtech.com/sc/course-list/
- Course Games202: https://www.bilibili.com/video/BV1YK4y1T7yY?p=1
- [https://www.youtube.com/@ChiliTomatoNoodle](https://www.youtube.com/playlist?list=PLqCJpWy5Fohe8ucwhksiv9hTF5sfid8lA)
- Game Engine Architecture, 3rd Edition.
- Design Patterns - Elements of Reusable Object-Oriented Software. 1997.
- Game Programming Patterns. 2014.
