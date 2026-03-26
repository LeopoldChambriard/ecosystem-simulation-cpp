cat << 'EOF' > README.md
# Multi-Agent Ecosystem Simulation (C++)

A 2D multi-agent simulation of autonomous aquatic creatures ("Bestioles") moving, sensing, and interacting within a closed ecosystem ("Aquarium"). The project focuses on rigorous object-oriented design and design patterns to ensure extensibility, maintainability, and clean separation of concerns.

---

## Architectural Highlights & Design Patterns

The architecture relies on classic Gang of Four (GoF) design patterns:

* **Decorator Pattern (`CapteursEtAccessoires/`)**: Dynamically equips creatures with physical accessories (fins, shells, camouflage) and sensory organs (eyes, ears) without altering the core `Bestiole` class.
* **Strategy Pattern (`Comportements/`)**: Decouples motion decision logic from the creature state, supporting swappable behaviors (`Gregaire`, `Kamikaze`, `Peureuse`, `Prevoyante`, `PersonnalitesMultiples`).
* **Factory Pattern (`Creation/`)**: Encapsulates creature instantiation and population configuration parameters via `BestioleFactory`.
* **Visitor Pattern (`Visitor/`)**: Applies external processing operations across heterogeneous creature hierarchies without polluting their interfaces.
* **Observer Pattern (`Observation/`)**: Tracks simulation statistics and metrics over time via `IObservateur` and `JournalSimulation`.

---

## Project Structure

```text
├── Bestioles/               # Base entity models, decorator interfaces, and core creature logic
├── CapteursEtAccessoires/   # Decorator implementations (DecYeux, DecNageoires, DecCarapace, etc.)
├── Comportements/           # Behavior strategies (Gregaire, Kamikaze, Peureuse, etc.)
├── Creation/                # Factory and population setup classes
├── Observation/             # Observer pattern metrics and loggers
├── Simulation/              # Environment (Milieu) and window loop (Aquarium)
├── Visitor/                 # Visitor pattern interfaces and concrete operations
├── Lib/                     # CImg image processing library for graphical rendering
├── Makefile                 # Compilation setup
└── main.cpp                 # Simulation entry point