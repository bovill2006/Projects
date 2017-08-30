using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace CSE445Assignment3
{
    class TravelAgency
    {

        /*
         TravelAgency1 through TravelAgencyN, each travel agency is a thread
         instantiated from the same class (or the same method) in a class.
         The travel agency’s actions are event-driven. Each travel agency
         contains a call-back method (event handler) for the HotelSuppliers
         to call when a price-cut event occurs. The travel agency will
         calculate the number of rooms to order, for example, based on the
         need and the difference between the previous price and the current
         price. The thread will terminate after the HotelSupplier thread has
         terminated. Each order is an OrderClass object. The object is sent
         to the Encoder for encoding. The encoded string is sent back to the
         travel agency. Then, the travel agency will send the order in String
         format to the MultiCellBuffer. Before sending the order to the
         MultiCellBuffer, a time stamp must be saved. When the confirmation of
         order completion is received, the time of the order will be calculated
         and saved (or printed). You can set N = 5 in your implementation.
         */


        /*********************************
         * 
         * This thread uses the agency thread(s) while the function below this
         * one uses the hotel thread(s) this is a problem for output
         * 
         **********************************/ 
        public static void travelAgencyFunc()
        {
            //Console.WriteLine("agency thread started");
            HotelSupplier hotel = new HotelSupplier();
            
            /****************************
            * 
            *Below lines keep track of when the hotelSupplier threads finish
            *Once it finishes the travelAgency threads should finish too
            *
            *****************************/
            int priceCuts = hotel.getPriceCuts();
            while(priceCuts < 10)
            //for (Int32 i = 0; i < 10; i++)
            {
                //CALLS FUNCTION TO ADD ORDER OBJECTS TO BUFFER
                //addtoBuffer();

                Thread.Sleep(1000);

                Int32 price = hotel.getPrice();

                Console.WriteLine("{0} has everyday low price: ${1} each", Thread.CurrentThread.Name, price); // Thread.CurrentThread.Name prints thread name
                priceCuts = hotel.getPriceCuts();
            }

        }
        /******************************************
         * 
         * This method uses the hotel thread(s) while the above method 
         * uses the agency thread(s) which is a problem for output
         * 
         *****************************************/
        public void hotelOnSale(Int32 price)
        {  
            // Event handler --- This method is automatically called when there is a pricecut. This IS working now.

            Console.WriteLine("\nPrice Cut: {0} has rooms for sale at a price of: ${1}!", Thread.CurrentThread.Name, price); // Thread.CurrentThread.Name cannot print a name
            addtoBuffer();
        }

        static object lock5 = new object();
        public static void addtoBuffer()
        {
            //TO-DO: Create Order Object, then send order object to encoder. 
            //The encoder should return order object as a string. 
            //Add the string to the buffer.

            //TO-DO: A time stamp must be saved before sending the order to the buffer.

            //Example of creating an orderObject, encoding it, and then sending it into the buffer
            Encoder encode = new Encoder();
            /************************************
             * 
             * We still need to figure out how to put the correct information into the order object
             *
             *************************************/
            string[] agencies = new string[5] { "Expedia", "Hotwire", "Orbitz", "Priceline", "Travelocity"};
            Random rng = new Random();
            Int32 agencyNumber = rng.Next(0, 5);

                OrderObject order = new OrderObject(agencies[agencyNumber], Program.bs.create(), Thread.CurrentThread.Name, 5);
                string encodedOrder = encode.encode(order);
                Console.WriteLine("\n{0} received an order from {1}.", Thread.CurrentThread.Name, agencies[agencyNumber]);
                Program.mb.setOneCell(encodedOrder);
            
        }

    }
}
