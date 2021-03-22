# Start server
`cd Example-Cpp`

`make && ./server`

# Start client

`cd Example-Node`

`npm install`

`npm run generate`

`node . <USERNAME> <LIST_OF_ITEMS> <MODE>`

## Parameters:
- USERNAME: username used when logging in
- LIST_OF_ITEMS: comma-separated string of items to fetch, e.g: "ItemA,ItemD". Supported items: ItemA, ItemB, ItemC, ItemD.
- MODE: if set to "multimode", client will communicate to the server it can fetch multiple items at once. If set to any other value, client will fetch only one item at a time.

Example: `node . root ItemB,ItemD,ItemC multimode`