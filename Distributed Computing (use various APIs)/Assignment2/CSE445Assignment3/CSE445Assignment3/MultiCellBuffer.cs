using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace CSE445Assignment3
{
    class MultiCellBuffer
    {
        /*
         MultiCellBuffer class is used for the communication between the travel agencies (clients)
         and the HotelSupplier (server): This class has n data cells
         (for individual project, n = 2 and for group project, n = 3). The number of cells available
         must be less than (<) the max number of travel agencies in your experiment. A setOneCell
         and getOneCell methods can be defined to write data into and to read data from one of the
         available cells. You must use a semaphore of value n to manage the cells and use a lock on
         each buffer cell. You cannot use a queue for the buffer, which is a different data structure.
         But the HotelSupplier can still read at the same time. Synchronization is also required. 
         */
        const int SIZE = 3;
        int head = 0, tail = 0, nElements = 0;
        string[] buffer = new string[SIZE];

        Semaphore write = new Semaphore(1, 1);
        Semaphore read = new Semaphore(2, 2);


        public void setOneCell(string n)
        {
            write.WaitOne();
            //Console.WriteLine("Thread : " + Thread.CurrentThread.Name + " Entered Write");
            lock (this)
            {
                while (nElements == SIZE)
                {
                    Monitor.Wait(this);
                }

                buffer[tail] = n;
                tail = (tail + 1) % SIZE;
                //Console.WriteLine("WBuf: {0}, {1}, {2}", n, DateTime.Now, nElements);
                nElements++;
                //Console.WriteLine("Thread : " + Thread.CurrentThread.Name + " Leaving Write");
                write.Release();
                Monitor.Pulse(this);

            }
        }

        public string getOneCell()
        {
            read.WaitOne();
            //Console.WriteLine("Thread : " + Thread.CurrentThread.Name + " Entered Read");
            lock (this)
            {
                string element;
                while (nElements == 0)
                {
                    Monitor.Wait(this);
                }

                element = buffer[head];
                head = (head + 1) % SIZE;
                nElements--;
                //Console.WriteLine("Read from the buffer: {0} , {1}, {2}", element, DateTime.Now, nElements);
                //Console.WriteLine("Thread : " + Thread.CurrentThread.Name + " Leaving Read");
                read.Release();
                Monitor.Pulse(this);
                return element;
            }

        }

        public bool isEmpty()
        {
            if(nElements != 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}
