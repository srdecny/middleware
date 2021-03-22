const thrift = require('thrift');
// Generated module
const Login = require('./gen-nodejs/Login.js');
const Search = require('./gen-nodejs/Search.js');
const Reports = require('./gen-nodejs/Reports.js');
const {InvalidKeyException, ProtocolException, FetchState} = require('./gen-nodejs/Task_types.js');
// Connect to server by TCP socket
const connection = thrift.createConnection('localhost', 5000, {
    // Use buffering
    transport: thrift.TBufferedTransport,
    // Use a binary protocol to serialize data
    protocol: thrift.TBinaryProtocol
})

if (process.argv.length != 5) {
    console.log("Usage: node . <LOGIN_NAME> <QUERY> <MODE>")
    console.log("Query: comma-separated list of ItemA, ItemB, ItemC, ItemD")
    console.log("Mode: multimode for fetching multiple items at a time, otherwise only one item")
    process.exit(1)
}

login = process.argv[2];
query = process.argv[3];
multimode = process.argv[4] === "multimode";

(async () => {
// Use a multiplexed protocol to select a service by name
    const multiplexer = new thrift.Multiplexer();
    const loginClient = multiplexer.createClient("Login", Login, connection);

    let key = 1337;
    console.log(`Logging to the client with login: ${login} and key ${key}`)
    try {
        await loginClient.logIn(login, key) ;
    } catch (e) {
        if (e instanceof InvalidKeyException) {
            console.log(`Exception caught, expected key: ${e.expectedKey}`)
            key = e.expectedKey
        } else {
            throw e
        }
    }
    console.log(`Logging to the client with login: ${login} and key ${key}`)
    await loginClient.logIn(login, key)
    console.log(`Login OK!`)

    const searchClient = multiplexer.createClient("Search", Search, connection)
    fetchedItems = []
    try {
        console.log(`Sending search query: ${query}`)
        const state = await searchClient.search(query, 10);
        // UPDATED PART
        if (multimode) {
            console.log("Enabling multimode!")
            state.multimode = true;
        }

        let fetchRes = await searchClient.fetch(state)
        console.log(`Fetching item ${fetchRes.nextSearchState.fetchedItems}`)
        while (fetchRes.state != FetchState.ENDED) {
            if (fetchRes.state == FetchState.ITEMS) {
                // UPDATED PART
                if (fetchRes.items) {
                    console.log(`Received items: ${JSON.stringify(fetchRes)}`);
                    fetchRes.items.forEach(item => fetchedItems.push(item.itemA || item.itemB || item.itemC || item.itemD))
                } else {
                    console.log(`Received item: ${JSON.stringify(fetchRes)}`);
                    fetchedItems.push(fetchRes.item.itemA || fetchRes.item.itemB || fetchRes.item.itemC || fetchRes.item.itemD)
                }
            } else {
                console.log(`Item is still being fetched...`)
            }
            
            console.log(`Fetching item ${fetchRes.nextSearchState.fetchedItems}`)
            fetchRes = await searchClient.fetch(fetchRes.nextSearchState)
        }
        console.log(`Finished fetching`)
        
    } catch(e) {
        if (e instanceof ProtocolException) {
            console.log(`Protocol Exception: ${e.message}`)
        } else {
            throw e
        }
    }

    console.log(`Generating report...`)
    report = fetchedItems.reduce((acc, item) => {
        ["fieldA", "fieldB", "fieldC", "fieldD"].forEach(field => {
                if(item[field]) acc[field].push(item[field]["join"] ? item[field].join(",") : item[field].toString())
            })
        return acc
    }, {
        fieldA: [],
        fieldB: [],
        fieldC: [],
        fieldD: []
    })
    console.log(report)

    console.log("Saving report...")
    const reportClient = multiplexer.createClient("Reports", Reports, connection)
    const reportResult = await reportClient.saveReport(report)
    console.log(`Report accepted: ${reportResult}`)

    console.log("Logging out...")
    await loginClient.logOut()

    // Perhaps there's a proper way to close the connection, but I'm just keeping it simple
    process.exit(0)

})()