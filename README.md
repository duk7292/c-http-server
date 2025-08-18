# Simple HTTP Server in C

This is a tiny HTTP server I hacked together in **raw C**.  
The goal wasn’t to make something production-ready, but to learn how things work under the hood:
- How HTTP servers actually function
- How to write real programs in C (since I hadn’t really used C like this before)

---

## How It Works

- The server opens a **listening socket** and waits for incoming connections.  
- When a client connects, it spins up a **detached thread** to handle that request, while the main thread keeps listening for more.  
- In the worker thread:
  - The HTTP request is parsed and stored in a **hashmap**.
  - That hashmap gets passed to a simple response builder, which creates an HTTP response with headers and serves a file if it exists.

---

## Features

- Only handles **GET** requests.  
- Anything inside the `public/` folder can be served.  
  - Files outside of it are blocked.  
- handels a few different file types (check `contentTypeConversion.c`).  

---

## Things That Could Be Better

This is just a learning project, so I kept it super basic. Some improvements could be:
- Supporting more HTTP methods (POST, PUT, DELETE, …).
- Redirecting `/` to `index.html` automatically.
- Making it configurable.
- Adding proper error handling and logging.
- Smarter request parsing.

---

## Notes

This is **not meant for production**.  
It’s just a personal experiment to learn sockets, and HTTP basics in C.  

For now, I’m leaving it as it is, it does what I wanted, and I learned a lot in the process.
