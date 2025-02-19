# Data Stores
* [Classes](#DataStore)
    * [DataStore](#DataStore)
    * [File](#File)
    * [InMemoryStore](#InMemoryStore)
    * [SageMakerPipe](#SageMakerPipe)
* [Enumerations](#Enumerations)
    * [Compression](#Compression)
* [Functions](#Functions)
    * [list_files](#list_files)

A data store, as its name suggests, represents an entity that is used for storing binary or textual data. As of today ML-IO supports local files, in-memory buffers, and Amazon SageMaker pipe channels as data stores. 

## DataStore
Represents an abstract base class for all data store types.

### Methods
#### open_read
```python
open_read()
```

Returns an [`InputStream`](stream.md#InputStream) instance for reading from the data store.

### Properties
#### id
Gets a `str` that uniquely identifies the data store instance.

Note also that all data store instances are hashable and can be used in dictionaries and sets.

## File
Represents a local file as a data store. Inherits from [DataStore](#DataStore).

```python
File(pathname : str, mmap : bool = True, compression : Compression = Compression.INFER)
```

- `pathname`: The path to a file in the local file system.
- `mmap`: A boolean value indicating whether the file should be memory-mapped. A memory-mapped file usually offers faster read and write performance.
- `compression`: The [compression](#Compression) format of the file. If set to `INFER`, the compression will be inferred from the filename.

## InMemoryStore
Represents a block of memory as a data store. Inherits from [DataStore](#DataStore).

```python
InMemoryStore(buf : buffer, compression : Compression = Compression.INFER)
```

- `buf`: A Python object, such as a `memoryview` or an `array.array`, that implements the Python Buffer protocol.
- `compression`: The [compression](#Compression) format of the data.

## SageMakerPipe
Represents an Amazon SageMaker pipe channel as a data store. Inherits from [DataStore](#DataStore).

```python
SageMakerPipe(pathname : str, fifo_id : int = None, compression : Compression = Compression.INFER)
```

- `pathname`: The path of an Amazon SageMaker pipe channel on the local file system; by convention this is usually a path residing under `/opt/ml` (e.g. `/opt/ml/train`)
- `fifo_id`: (Advanced) The UNIX named pipe (a.k.a. FIFO) suffix of the channel. This parameter should only be used if you read from the pipe channel using another mechanism before instantiating a `SageMakerPipe` instance.
- `compression`: The [compression](#Compression) format of the pipe channel.

## Enumerations
#### Compression
Specifies the compression type used for the initialization of a data store.

| Value   | Description                                                                                           |
|---------|-------------------------------------------------------------------------------------------------------|
| `NONE`  | The data store contains uncompressed data.                                                            |
| `INFER` | The compression should be inferred from the data store; not all data store types support this option. |
| `GZIP`  | The data store contains data compressed in gzip or zlib format.                                       |
| `BZIP2` | Not implemented yet                                                                                   |
| `ZIP`   | Not implemented yet                                                                                   |

## Functions
#### list_files
A convenience function that returns a list of [`File`](#File) instances in natural sort order (see `strverscmp(3)`) after recursively traversing one or more directories.

 ```python
 list_files(pathnames : List[str], 
            pattern : str = None,
            predicate : Callback = None,
            mmap : bool = True,
            compression : Compression = Compression.INFER)
 ```

 - `pathnames`: One or more directory paths to traverse. In case a pathname points to a regular file, the file gets returned as if it was the result of a directory walk.
 - `pattern`: A glob pattern with wildcard characters (e.g. `*.csv`) to specify a subset of files to return.
 - `predicate`: A callback function in the form `callback(pathname : str) -> bool` that gets passed the full path of a file and that should return a boolean value indicating whether to include the file in the final list. Returning `True` means to include it; otherwise, it will be discarded.
 - `mmap`: A boolean value indicating whether the files should be memory-mapped. A memory-mapped file usually offers faster read and write performance.
 - `compression`: The [compression](#Compression) format of the files. If set to `INFER`, the compression will be inferred individually for each file.

 There is also a light version of `list_files()` with a simplified signature as described below:

 ```python
 list_files(pathname : str, pattern : str = None)
 ```
 - `pathname`: A directory path to traverse.
 - `pattern`: A glob pattern with wildcard characters (e.g. `*.csv`) to specify a subset of files to return.
