using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSE445Assignment3
{
    class OrderObject
    {
        private string senderId, receiverId;
        private int amount, cardNo;

        public OrderObject() { }

        public OrderObject(string sender, int card, string receiver,int am)
        {
            senderId = String.Copy(sender);
            cardNo = card;
            receiverId = String.Copy(receiver);
            amount = am; 
        }
        

        public void print()
        {
            Console.WriteLine("Sender: " + senderId);
            Console.WriteLine("The cardNo: {0} ", cardNo);
            Console.WriteLine("The ReceiverID: " + receiverId);
            Console.WriteLine("The amount: {0}", amount);
            Console.WriteLine();
        }


        public void setSender(string sender)
        {
            senderId = String.Copy(sender);
        }
        
        public void setCard(int card)
        {
            cardNo = card; 
        }

        public void setReceiver(string receiver)
        {
            receiverId = String.Copy(receiver);
        }
        public void setAmount(int a)
        {
            amount = a; 
        }

        public string getSender()
        {
            return senderId;
        }

        public int getCard()
        {
            return cardNo;
        }

        public string getRec()
        {
            return receiverId;
        }
        public int getAmount()
        {
            return amount; 
        }



                
        /*
        OrderClass is a class that contains at least the following private data members:
         
	    senderId: the identity of the sender, you can use thread name or thread id;
	    cardNo: an integer that represents a credit card number;
	    receiverID: the identity of the receiver, you can use thread name or a unique
            name that defined for a hotel supplier; If you are doing an individual project,
            you do not need this field.
         amount: an integer that represents the number of room to order;
         
	     You must use public methods to set and get the private data members. You must
         decide if these methods need to be synchronized. The instances created from this
         class are of the OrderObject.
         */
    }

}
