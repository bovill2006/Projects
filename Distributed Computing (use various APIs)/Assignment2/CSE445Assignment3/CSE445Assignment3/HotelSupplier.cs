using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using CSE445Assignment3.ServiceReference1;

namespace CSE445Assignment3
{
    class HotelSupplier
    {
        /*
         HotelSupplier1 through HotelSupplierK* are the objects of a class on the server side: 
         Each object has method to be started as a thread by the Main method and will perform 
         a number of functions. It uses a PricingModel to determine the room prices. It defines
         a price-cut event that can emit an event and call the event handlers in the 
         TravelAgencys if there is a price-cut according to the PricingModel. It receives the
         orders (in a string) from the MultiCellBuffer. It callas the Decoder to convert the string
         into the order object. For each order, you can use the existing thread or start a new
         thread (resulting in multiple threads for processing multiple orders) from OrderProcessing
         class (or method) to process the order based on the current price. There is a counter p
         in the HotelSupplier. After p (e.g., p = 10) price cuts have been made, a HotelSupplier
         thread will terminate.    
         
         PricingModel: It can be a class or a method in HotelSupplier class. It decides the price
         of rooms. It can increase price or decrease the price. You must define a mathematical
         model (random function is fine) to determine the price based on the order received within
         a given time period and the number of rooms available in the HotelSupplier in the same
         time period. You can use a hard-coded table of the price in each week day. However, you
         must make sure that your model will allow the price goes up some time and goes down some
         other time. 
         */

        //Event handling stuff
        public static event priceCutEvent priceCut; // Link event to delegate

        //Other Variables
        static Random rng = new Random(); // To generate random numbers
        /*******************************
         * 
         *To keep track of number of price cuts (At 10 the threads are supposed to terminate)
         *
         **************************/

        private static Int32 p = 0;
        private static bool orderStarted = false;

        /**************************
         * 
         *Made staring roomprice high so that first price is always newest lowest
         *We may want to change this depending on how we want this program to start
         * 
         ***************************/
        private static int salePrice = 150;
        public Int32 getPrice() { return salePrice; }

        public Int32 getPriceCuts() { return p; }
        //Pricing Model

        static object lock1 = new object();
        public static void pricingModel(Int32 price)
        {
            if (price < salePrice)
            { // a price cut
                /*********************
                 * 
                 *increment pricecut counter (p++)
                 *if there has been 10 or less price cuts, continue (if clause)
                 *
                 ********************/
                salePrice = price;
                p++;
                if (priceCut != null && p <= 10)  // there is at least a subscriber
                {
                    //Console.WriteLine("Pricecut event #"+p+" produced by "+Thread.CurrentThread.Name);
                    //Calls hotelOnSale(price) in travelAgency

                    priceCut(price);
                    //Console.WriteLine("Reading buffer for pricecut# " + p);

                }
            }
            salePrice = price;
        }

        static object lock2 = new object();
        public static void hotelSupplierFunc()
        {
            /*************************
             * 
             *changed function so that it only continues if there has been 10 or less price cuts
             *
             * ***********************/

            while (p <= 10)
            {
                lock (lock2)
                {
                    Thread.Sleep(500);

                    Int32 newPrice = rng.Next(30, 100);


                    // Take the order from the queue of the orders;


                    // Decide the price based on the orders

                    // Console.WriteLine("New Price is {0}", p);

                    HotelSupplier.pricingModel(newPrice);
                }
                if (!Program.mb.isEmpty())
                {
                    readFromBuffer();
                }

            }


        }

        public static void readFromBuffer()
        {
            //Get a value from the buffer. Normally this will be an encoded OrderObject
            //In which case we would then pass the string to the decoder to turn it back into and OrderObject
            string encodedOrder = Program.mb.getOneCell();

            //TO-DO: Decode the string 
            Decoder decode = new Decoder();
            OrderObject order = new OrderObject();
            order = decode.decode(encodedOrder);

            //TO-DO: Process the order

            Console.WriteLine(Thread.CurrentThread.Name + " PROCESSING ORDER");
            new Thread(delegate()
            {
                OrderProcessing(order);
            }).Start();
        }

        public static void OrderProcessing(OrderObject order)
        {
            Console.WriteLine("\n\n\nValidating credit card number...");
            Console.WriteLine("*********************ORDER CONFIRMATION***********************");


            //TO-DO Call BankService to validate credit card

            string c = Convert.ToString(order.getCard()); // card encrypt 
            ServiceClient convert = new ServiceClient();
            c = convert.Encrypt(c);

            //IF credit card is valid do the following
            if (Program.bs.validate(c))
            {
                //Calcuates total charge for room order
                double totalCharge = ((double)order.getAmount() * (double)salePrice * .1) + ((double)order.getAmount() * (double)salePrice);

                //Send confirmation back to travelAgency
                Console.WriteLine("{0} has successfully placed order with {1} for {2} rooms.", order.getSender(), order.getRec(), order.getAmount());
                Console.WriteLine("Price: {0} (${1} x {2})", ((double)order.getAmount() * (double)salePrice), (double)salePrice, (double)order.getAmount());
                Console.WriteLine("Tax: ${0}", ((double)order.getAmount() * (double)salePrice * .1));
                Console.WriteLine("Grand Total: ${0} \nCard Number: {1}", totalCharge, order.getCard());
                Console.WriteLine("*********************************************************\n\n\n");
            }
            else
            {
                //Send message back to travelAgency saying creditCard invalid
                Console.WriteLine("Error: Agency {0} could not place order with {1} due to invalid card number: {2}", order.getSender(), order.getRec(), order.getCard());
            }
        }
    }
}
