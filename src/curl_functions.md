Tjatte on CURL functions in http.c/h

Absolutely! Let’s break down your `http_curl` and `http_write_data` functions in detail, step by step, including why they are written that way and how the pointers and memory management work. I’ll explain it clearly, even if some parts look subtle.

---

## **1. `http_write_data`**

This function is a **callback** that libcurl calls repeatedly whenever a chunk of data is received from the HTTP response.

### **Signature**

```c
size_t http_write_data(void *buffer, size_t size, size_t nmemb, void *userp);
```

* **`buffer`**: pointer to the raw bytes received from the HTTP response for this chunk.
* **`size`**: size in bytes of a single element (usually 1).
* **`nmemb`**: number of elements in this chunk.
* **`userp`**: pointer you passed to `CURLOPT_WRITEDATA` — in this case, it points to a `http_membuf_t` struct where we accumulate the response.

Libcurl’s rule:

> The function must return the number of bytes it successfully handled. Returning anything else signals an error.

---

### **Step-by-step**

```c
size_t bytes = size * nmemb;
```

* Calculate the total number of bytes in this chunk.
* Sometimes `size` may not be 1, so we multiply by `nmemb`.

```c
struct http_membuf_t* mem_t = (struct http_membuf_t*)userp;
```

* `userp` is a void pointer. Cast it back to our `http_membuf_t*` so we can access the buffer and size.

```c
char *ptr = realloc(mem_t->data, mem_t->size + bytes + 1);
```

* Grow the buffer dynamically to accommodate the new chunk.
* `mem_t->size` is how much we already have, `bytes` is new data, and `+1` is for the null terminator (`\0`) to treat it as a string.

```c
if (!ptr) {
    printf("Memory allocation failed!\n");
    return 0;
}
```

* Always check `realloc` in case of failure. Returning `0` tells libcurl to abort the transfer.

```c
mem_t->data = ptr;
memcpy(&(mem_t->data[mem_t->size]), buffer, bytes);
mem_t->size += bytes;
mem_t->data[mem_t->size] = '\0';
```

* Copy the new chunk to the **end of the existing buffer**.
* Update the total size.
* Add a null terminator so the buffer can be treated as a C string later.

```c
return bytes;
```

* Tell libcurl that we successfully handled all bytes.

---

### **Summary of `http_write_data`**

* Accumulates chunks of the HTTP response dynamically.
* Uses `realloc` to grow the buffer safely.
* Ensures null termination so it can be printed as a string.
* Returns the number of bytes handled so libcurl knows it’s OK.

---

## **2. `http_curl`**

This function is the **wrapper for making an HTTP GET request** using libcurl.

### **Signature**

```c
int http_curl(parse_city_t *city_array, short int *cc, char **curl_buf, size_t *curl_buf_len);
```

* **`city_array`**: array of cities with names and URLs.
* **`cc`**: index of the selected city.
* **`curl_buf`**: pointer to a pointer that will receive the dynamically allocated buffer with the HTTP response.
* **`curl_buf_len`**: pointer to store the length of the buffer.

---

### **Step-by-step**

```c
CURL *curl = curl_easy_init();
if (!curl) { ... }
```

* Initialize a CURL handle. Must check if it succeeded.

```c
struct http_membuf_t chunk = {0};
```

* Create a buffer structure to store the downloaded data.
* Initially, `chunk.data = NULL` and `chunk.size = 0`.

---

#### **Setting CURL options**

```c
curl_easy_setopt(curl, CURLOPT_URL, city_array[*cc].city_url);
```

* Set the URL to request based on the selected city.

```c
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_write_data);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
```

* Tell libcurl to call `http_write_data` for every chunk received.
* Pass a pointer to `chunk` as `userp` so `http_write_data` can accumulate the data.

```c
curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
```

* Follow HTTP redirects automatically.

---

#### **Perform the request**

```c
CURLcode res = curl_easy_perform(curl);
if (res != CURLE_OK) { ... }
```

* Performs the HTTP GET synchronously.
* If an error occurs, cleanup and free any allocated memory.

---

#### **Cleanup and return**

```c
curl_easy_cleanup(curl);
*cc = 16;
*curl_buf = chunk.data;
*curl_buf_len = chunk.size;
```

* `curl_easy_cleanup` frees internal CURL resources.
* `chunk.data` now contains the full response — pass it back to `main`.
* `*curl_buf_len` stores the size of the response.
* Reset city counter in main (`*cc = 16`) to indicate the request is complete.

---

### **Memory ownership**

* `chunk.data` is dynamically allocated by `realloc` inside `http_write_data`.
* Ownership is **transferred to the caller** (`main.c`), which must call `free()` after using the buffer.

---

### **Summary of `http_curl`**

1. Initialize CURL handle.
2. Prepare a dynamic buffer (`http_membuf_t`) to store the response.
3. Set URL, write callback, and options.
4. Perform the request.
5. If successful, return the buffer and its length to the caller.
6. Cleanup CURL resources.
7. The caller is responsible for freeing the memory.

---

### **Why this pattern is used**

* **Callback design**: libcurl doesn’t return the entire response at once; it streams chunks. A callback is needed to handle arbitrary-sized responses.
* **Dynamic buffer**: prevents buffer overflow and allows variable-length responses.
* **Pointer-to-pointer** (`char **curl_buf`): allows the function to allocate memory internally and return it to the caller safely.
* **Null termination**: ensures the buffer can be printed as a string (`printf("%s")`) without crashing.

---

💡 **Analogy:**
Think of `http_write_data` as a bucket that keeps catching water drops (chunks of data) and growing bigger as more drops fall. `http_curl` is the faucet controlling the flow and eventually handing the full bucket to you.

---

If you want, I can also draw a **diagram showing the flow of pointers and memory between `main`, `http_curl`, and `http_write_data`** — it really helps visualize why `char **curl_buf` is necessary.

Do you want me to do that?
