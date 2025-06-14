## Andvanced Algorithms
---

## 🧠 Assignment I: Pattern Matching and Advanced String Algorithms

### Part 1: "Mom bought me a new computer"

Implemented algorithms:
- Brute-force
- Sunday
- Knuth–Morris–Pratt (KMP)
- Finite State Machine (FSM)
- Rabin-Karp
- Gusfield Z

**Goal:** Compare runtime performance using:
- Short patterns (few words)
- Long patterns (paragraphs)
- Multiple input sizes (chapters of a book)

📊 *Report includes*: 
- Time vs Text Length graphs
- Analysis and reproducibility details

📄 [Read the full report on Google Docs](https://docs.google.com/document/d/1lFmbaIyB9rusFcrnIlUnMgozEhcXEmU3iVDdMQpe_ZE/edit?tab=t.0)


---

### Part 2: "Wacky Races"

**Goal:** Demonstrate algorithm-specific strengths with examples where:
- Binary Sunday is at least 2× faster than Gusfield Z
- KMP is at least 2× faster than Rabin-Karp
- Rabin-Karp is at least 2× faster than Sunday

🧪 *Includes*: Custom inputs of ≥100kB with commentary and explanation.

---

### Part 3: "Jewish-style carp"

**Goal:**  
Find whether the top-right `K x K` square of an `M x N` 2D image appears elsewhere using a fast Rabin-Karp variant.

💡 *Optimizations*:
- Replace modulo operations with bitwise masking (`&`)
- Runtime: O(pixels)

---

## 🧠 Assignment II: Data Structures, Graphs & Hashing

### Part 1A: "Me spell rite"

**Goal:**  
Spell checker using various data structures:
- Naive linear list
- Balanced BST (e.g., `std::set`)
- Trie
- Hash Map

📊 *Comparison*: 
- Dictionary build time
- Word lookup time
- Graphs: Runtime vs Input Size

---

### Part 1B: "Triwizard Tournament"

**Goal:**  
Simulate a shortest path race between three wizards using BFS.

🧭 Given:
- Labyrinth map
- Start positions
- Speeds (in cells/min)

🔍 Uses BFS once to determine shortest paths for all.

---

### Part 2: "Aunt's Namesday"

**Goal:**  
Use non-recursive DFS to split party guests into two tables so that no pair of enemies sits together.

📎 Input:  
Guest list + “dislikes” relationships (conflict graph)

📐 Output:  
Two groups with no internal conflicts

---

### Part 3: "Full House"

**Goal:**  
Implement three Hash Table variants:
- Separate Chaining
- Linear Probing
- Double Hashing

📊 *Graph*: Search/Insert Time vs Load Factor  
🔬 *Result Analysis*: Hash performance trends and trade-offs
