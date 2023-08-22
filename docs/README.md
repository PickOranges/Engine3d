# Engine3d
Graphics Engine for learning purpose. Written in C++ and DirectX11/HLSL. [Click here to view source code.](https://github.com/PickOranges/Engine3d/tree/develop_sm)

## Features
- Message/Event Queue (to deal with both rendering ticks and gameplay logic ticks)
- Reflection Mechanism (loading models without specifying vertex attributes manually)
- Render Graph
- Render Queue System (multi-pass system)
- Exception Handling
- Scene Graph (organizes model nodes and meshes with a tree-like structure)
- Resource Pool
  
- Normal Mapping
- Gauss Filter
- Outline Effect via Stencil Buffer (Highlights Mouse-Picked Submesh)

## Sceenshots
![Screenshot (130)](https://user-images.githubusercontent.com/55946962/167479209-ab5b1ccb-15bc-4bc1-ae3d-b36d055f4892.png)

## Dependencies
- ImGui
- assimp
- DirecXTex
- Windows API

## References
- Course Games104: https://games104.boomingtech.com/sc/course-list/
- Course Games202: https://www.bilibili.com/video/BV1YK4y1T7yY?p=1
- https://www.youtube.com/@ChiliTomatoNoodle
- Game Engine Architecture, 3rd Edition.
- Design Patterns - Elements of Reusable Object-Oriented Software. 1997.
