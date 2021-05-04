# Workarounds
I did not manage to define the EntryProcesors inline, in Client.java because of serialization issues, so they're in separate files. 

# Requirements on stored maps

## Document map
This is the main document map. As this map can be the largest and documents can be regenerated, this is the map that should be evicted from memory first. By default, there is no eviction policy. Because the documents are not time-sensitive, it does not make sense to use time-to-live or max-idle-seconds. Least Frequently Used eviction policy was chosen. There is no max size, because we want to have as much documents in the memory as possible.

By-default, the map has 1 backup. This is not necessary, as we can restore the documents, so the backups are set to 0 to save memory.

## Comments, views and favourite lists
These maps contain critical information that cannot be restored back. These maps are also expected to be small enough to not cause any memory issues. Thus, the amount of backup copies is raised to a arbitrarily chosen number larger than 1, such as 3.

## Selected document
This map is not critical enough to warrant multiple backups (user can siply select the document again), so the configuration is left in the default state.