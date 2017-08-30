using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace CSE445Assignment3
{
    public delegate void priceCutEvent(Int32 pr); // Define a delegate
    class Program
    {
        public static MultiCellBuffer mb = new MultiCellBuffer();
        public static BankService bs = new BankService();
        static void Main(string[] args)
        {
            //BankService a = new BankService();
            //int c = a.create();
            //Console.WriteLine(c);
            
            //Console.WriteLine(a.validate(c));
            //Console.ReadLine();

            //To ensure we are seeing all of output
            Console.WriteLine("==========HOTEL PRICE PROGRAM STARTED==========\n");   
           
            //Thread spawning for HotelSuppliers and TravelAgencies
            //We will have an array of 5 TravelAgency threads and 3 HotelSupplier threads
            Thread[] hotelThread = new Thread[3];
            Thread[] agencyThread = new Thread[5];
             
            //Loop to spawn and start all of the threads for hotel
            for (int i = 0; i < 3; i++)
            {
                hotelThread[i] = new Thread(HotelSupplier.hotelSupplierFunc);
                if(i == 0)
                    hotelThread[i].Name = "Comfort Inn";
                else if(i == 1)
                    hotelThread[i].Name = "Holiday Inn";
                else
                    hotelThread[i].Name = "Motel 6";

                hotelThread[i].Start();
            }

            /************************
             * 
             * We may need to change something here to deal with 
             * method problem talked about in TravelAgency.cs
             * 
             ************************/
            TravelAgency agency = new TravelAgency();
            HotelSupplier.priceCut += new priceCutEvent(agency.hotelOnSale);

            //Loop to spawn and start all the threads for Travel
            for (int i = 0; i < 5; i++)
            {
                agencyThread[i] = new Thread(TravelAgency.travelAgencyFunc);
                agencyThread[i].Name = "Agency #" + i;
                agencyThread[i].Start();

            }
            
            //Loop to call the join function of all the spawned threads, in this way, they will wait for each other to finish.
            for (int i = 0; i < 3; i++)
            {
                hotelThread[i].Join();
                Console.WriteLine("JOINAGE OF HOTEL " + i);
            }
            
            
            for (int i = 0; i < 5; i++)
            {
                agencyThread[i].Join();
                Console.WriteLine("JOINAGE OF AGENCY " + i);

            }
            

           
            
            Console.WriteLine("\n\nDone\n\n");
            Console.ReadLine();


            /*
             Main: The Main thread will perform necessary preparation, create the buffer classes,
             instantiate the objects, create threads, and start threads.
             */

            /*Additional tasks since we are a team:
              [1] You must implement multiple suppliers with K = 3. You must deal with all
                    the issues that are incurred because of the increase of the supplier number.
              [2] The supplier must send a confirmation back to the travel agency when an order is completed.	
              [3] The buffer size (number of cells in the buffer) is 3, instead of 2.
              [4] If you have a three-member team, you must also define the bank service.
            */
        }
    }
}
