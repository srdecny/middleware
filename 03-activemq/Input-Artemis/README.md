# Running
Make sure to change the setenv to point to a valid apache-artemis path.

# Communication protocol
To pass around data about the order, ObjectMessage was used, along with dedicated classes (SaleConfirmation, SaleReply). This was done to avoid setting multiple fields on an MapMessage. To pass around metadata about the message itself (when there were multiple types of messages in a single Topic/Queue), properties were used, so the message types could be distinguished. 

When there's an issue with the transaction (low balance), the bank notifies the seller. This is so seller can cancel the trade and buyer does not have to watch two queues -- the bank one, in case the transaction fails, and the seller queue, in case insufficient amount is sent.