# Log Database

> World's simplest database.

### Simple Write & Read

- Append writes = O(1)
- Read = O(n)

A textfile that utilizes two functions of get and set. set will do an append write on the textfile. Since set appends to file if you update a key several times, the old versions of the value will not be overwritten resulting in several copies of the key. You must see the last occurence of a key in a file to find the latest value.

Get is terrible performance if you have a large number of records in your database. Everytime you want to look up a key, you have to scan the entire database from beginning to end. 

To improve performance then we can utilize a different data structure called an Index. This additional metadata can help you locate the data you want. The Index is an additional structure that is derived from the primary data. You can add or remove indexes in most databases and not affect the content of a database, but you will only affect the performance of queries. The index will improve reads, but will slow down performance on write operations (comparing between O(1) time of appending at end.

### Hash Index

- Append writes O(1)
- Read = O(n)
- Utilizing In memory cache and possible cache file.

Adding onto this simple write and read log. We can also utilize something of a hash index. Whenever you append to the data file you can keep both the key and byte offset for an in-memory hash map to quickly retrieve data without having to parse through the entire data file for the key. This only requires all the keys to fit in the available RAM. This means that values can technically be loaded with one disk seek then if that data is part of filesystem cache then a read doesnt require any disk I\O at all.

This may be suitable for a situation for when you perform multiple writes frequently for each key. For example like updating information on a URL and how many times it has been viewed.

When there is no more disk space for the in memory hash table then we can simply write to a new segment file. Once this new segment file has been filled as well, then we can perform compaction on these segments meaning to throwaway duplicate keys in the log and keep only the most recent update for each key.A large constraint of utilizing this is the memory limit for cache, data disk space, etc. to keep performance and space.


