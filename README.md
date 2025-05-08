# Unreal Engine 5 ITD Parser 🛠️

> **Purpose**   
> Import and render **`.itd` (Industrial 3D Printing)** files natively inside **Unreal Engine 5**.  
> The plug-in parses vertex / normal / polygon data, converts it to `UStaticMesh`, and resolves _Non-Manifold_ issues while keeping the engine’s **Manifold-oriented** philosophy.

---

## ✨ Key Features
| Feature | Details |
|---------|---------|
| **Custom Importer & Factory** | Extends UE5 asset pipeline (`UFactory`, `FAssetImportData`) to recognise `.itd` files. |
| **Mesh Builder Integration** | Generates `FRawMesh` → `UStaticMesh`; reorders edges to avoid Non-Manifold crashes. |
| **Performance Optimisation** | Internal pruning reduced redundant build steps by **29 %**, lowering import time. |
| **Diagnostic Viewer** | Optional debug flag draws parsed polygons in-editor for quick validation. |

---

## 🚀 Quick Start

```bash
# 1) Clone to YourProject/Plugins
git clone https://github.com/FrogRim/UE5-ITD-Parser.git Plugins/ITDParser

# 2) Generate project files & build (VS2022, Win64 Development Editor)
./GenerateProjectFiles.bat
cmake --build . --config Development --target UE5Editor

# 3) Enable the plug-in inside Edit ▸ Plugins ▸ Importers
# 4) Re-start the editor and drag-drop a .itd file into the Content Browser
````

> **Note:** Engine source build tested on **UE 5.2 / 5.3** with Visual Studio 2022.

---

## 🏗️ Project Structure

```
ITDImporter/
 ├─ Factories/          # UFactory-derived classes
 ├─ Parsers/            # Binary reader for .itd chunks
 ├─ MeshBuilder/        # FRawMesh assembly + Non-Manifold fix
 └─ Tests/              # Unit tests (GTest)
Resources/              # Sample .itd models
Docs/                   # Additional build guides (KR/EN)
```

---

## 📊 Performance Snapshot

| Scene           | Triangles | Import Time (before) | Import Time (after) | Δ      |
| --------------- | --------- | -------------------- | ------------------- | ------ |
| Industrial Pump | 1.2 M     | **12.6 s**           | **9.0 s**           | ▼ 29 % |
| Pipe Array      | 850 k     | 8.3 s                | 6.1 s               | ▼ 26 % |

> *Non-Manifold edge fix eliminated 100 % of previous crash cases on these models.*

---

## 🧩 How It Works

1. **Byte-level Parser** scans `.itd` header → vertex / normal / face blocks.
2. **Topology Validator** reorders edges, splits Non-Manifold vertices when necessary.
3. **Mesh Builder** feeds `FStaticMeshOperations::BuildStaticMesh` with clean data.
4. **Asset Registry** registers the new `UStaticMesh` for immediate use in editor or runtime.

---

## 🔭 Roadmap

* [ ] **Material table** support (diffuse / roughness from .itd metadata)
* [ ] **Async import** to minimise editor hitching
* [ ] Prototype **Neural Super-Resolution** pass (ESRGAN) for large CAD scenes

---

## 📝 Build Notes & Troubleshooting

| Issue                                | Fix                                                                                              |
| ------------------------------------ | ------------------------------------------------------------------------------------------------ |
| `MSB3073 code 6` during engine build | Run **VS Developer Prompt** as admin and execute `Build.bat` manually to reveal missing SDKs.    |
| Editor crash on import               | Ensure “Enable Nanite” is disabled for > 50 M triangle raw meshes until Nanite support is added. |
| Corrupted normals                    | Toggle **Recalculate Normals** in plug-in settings; some legacy .itd files omit normal vectors.  |

---

MIT License © 2024 Lee Kang-Rim



