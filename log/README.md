# Log Database

> World's simplest database.

- Append writes = O(1)
- Read = O(n)

A textfile that utilizes two functions of get and set. set will do an append write on the textfile. Since set appends to file if you update a key several times, the old versions of the value will not be overwritten resulting in several copies of the key. You must see the last occurence of a key in a file to find the latest value.

Get is terrible performance if you have a large number of records in your database. Everytime you want to look up a key, you have to scan the entire database from beginning to end. 

To improve performance then we can utilize a different data structure called an Index. This additional metadata can help you locate the data you want. The Index is an additional structure that is derived from the primary data. You can add or remove indexes in most databases and not affect the content of a database, but you will only affect the performance of queries. The index will improve reads, but will slow down performance on write operations (comparing between O(1) time of appending at end)
