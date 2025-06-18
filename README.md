# cgrep

A project for me to learn a bit about programming in C.

### Usage
```sh
cgrep [pattern] [optional path] [optional flags...]
```

The program can be run with a single argument - a regex pattern, and will search the current directory and sub-directories for matches:

<img width="720" alt="image" src="https://github.com/user-attachments/assets/37406615-b9a7-4795-9960-3d37b8eafefd" />

---

An optional second argument can be passed, a path to a file or directory to search:

<img width="739" alt="image" src="https://github.com/user-attachments/assets/eabbaa36-32d9-4149-97a6-36cfa47fbbc0" />

---

An optional flag can be passed, `--json`, that will format the output as json:

<img width="739" alt="image" src="https://github.com/user-attachments/assets/3bbc904a-b8e2-487b-8d2c-a87747983ca8" />

### flags
`--json` - format output as json
