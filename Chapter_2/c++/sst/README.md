# Sorted String Table

Arranging key-value pairs to sort by key without prioritizing how they are ordered. This is done using a Sorted String Table. In a SSTable you cannot append new key-values pairs to the segments immediately, since writes can occur in any order. If we collect and keep all the key-values in order. We can then utilize a sparse index to quickly locate specific values without needing to track every single key-value in a segment. A sparse index will only index a few kb or even a specific amount of records to quickly locate them based on the values located such as knowing handiwork must be in-between handbag and handsome.

SSTables can utilize AVLTrees or Red-Black Trees to make sure you can insert keys in any order and read them back in sorted order. This in-memory tree can be sometimes referred to as a memtable. Once this memtable has reached a certain threshold it should be written to disk and then new writes can continue to a new memtable instance. Reads can be performed by using first the in-memory memtable then using the most recent on-disk segment then reading the next segment. Time and time can utilize the compaction process in the background to combine segment files and to discard overwritten or deleted values.

Issues involve if the database crashes then the most recent writes which are on the memtable but not on the disk are lost. We can utilize a log which can be used to append every write which will not be in sorted order, but can be used in case of a crash.

## Performance Optimizations

based on the principle of merging and compacting sorted files. Algorithm can be slow when looking up keys that do not exist in the database since you first have to check the memtable then the segments all the way back to the oldest disk before you can be sure the key does not exist. In order to speed up this access you can utilze bloom filters which is a memory-efficient data structure for approximating the contents of a set. It can tell you if a key does not appear in the database, and thus save many unnecessary disk reads for nonexistent keys.

There are also two different strategies to determine the order and timing of how SSTables are compacted and merged. Most common options are size-tiered and leveled compaction. In size-tiered compaction, newer and smaller SSTables are successfully merged into older and larger SSTables. In leveled compaction, the key range is split up into smaller SSTables and older data is moved into separate "levels"

