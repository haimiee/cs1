## Memory Regions
| Region      | What it's for                   | Example                                    |
| ------------------ | ------------------------------- | ------------------------------------------ |
| **Stack**          | Local variables, function calls | `char arr[] = "hello";`                    |
| **Heap**           | Dynamically allocated memory    | `malloc(10)`                               |
| **Text/Code**      | Compiled instructions           | Your functions (`main`, etc.)              |
| **Read-Only Data** | String literals, constants      | `"hello"` stored with `char *s = "hello";` |
