# PROBLEM

The Reader-Writer problem  is an example of a synchronisation problem. There are two processes Reader and Writer that are sharing common resources e.g file at a time.
The former one only reads the database, whereas the latter one wants to update (that is, to read and write) the database. 
###
The problem is when one process starts writing the database and another performs starts reading the database at the same time then the system will go into an inconsistent state.
###
Another problem arises when one process starts writing the database and another process also starts writing. As both processes want to update the value of the data present in the file at the same time it will lead to the inconsistency in the database. 

### Reader-Writer is categorized into three variants.
### Give readers priority: 
when there is at least one reader currently accessing the resource, allow new readers to access it as well. This can cause starvation if there are writers waiting to modify the resource and new readers arrive all the time, as the writers will never be granted access as long as there is at least one active reader.
### Give writers priority:
here, readers may starve.
### Give neither priority: 
all readers and writers will be granted access to the resource in their order of arrival. If a writer arrives while readers are accessing the resource, it will wait until those readers free the resource, and then modify it. New readers arriving in the meantime will have to wait.
