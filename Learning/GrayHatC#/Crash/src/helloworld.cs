using System;

namespace hello_world{
	class MainClass {
		public static void Main(string[] args){
			string hello = "Hello World!";
			DateTime now = DateTime.Now;

			Console.WriteLine(hello);
			Console.WriteLine(" The date is " + now.ToLongDateString());
		}
	}
}
