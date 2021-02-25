using System;

namespace Interfaces{
	public interface IPerson {
		string Name {get; set;}
		int 	 Age 	{get; set;}
	}
}

namespace Classes{
	public abstract class PublicServant{
			public int PensionAmount{get; set;}
			public abstract void DriveToPlaceOfInterest();
	}

	public class Firefigther : PublicServant, Interfaces.IPerson{
		public string Name {get; set;}
		public int 	 Age 	{get; set;}

		public Firefigther(string name, int age){
				this.Name = name;
				this.Age  = age;
		}

		public override void DriveToPlaceOfInterest(){
			GetInFireTruck();
			TurnOnSiren();
			FollowDirections();
		}

		private void	GetInFireTruck(){}
		private void	TurnOnSiren(){}
		private void	FollowDirections(){}
		
	}	

	public class PoliceOfficer : PublicServant, Interfaces.IPerson {
		public string Name {get; set;}
		public int 	 Age 	{get; set;}

		private bool _hasEmergancy;

		public PoliceOfficer(string name, int age){
			this.Name			= name;
			this.Age			= age;
			_hasEmergancy = false;
		}

		public bool HasEmergancy{
			get { return _hasEmergancy;  }
			set { _hasEmergancy = value; }
		}

		public override void DriveToPlaceOfInterest(){
				GetInPoliceCar();
				if(this.HasEmergancy){
					TurnOnSiren();
				}
				FollowDirections();
		}

		private void	GetInPoliceCar(){}
		private void	TurnOnSiren(){}
		private void	FollowDirections(){}
	}
} 

namespace Main{

	class MainClass{
		public static void Main(string[] args){
			Classes.Firefigther firefigther = new Classes.Firefigther("Joe Carrington",35);	
			Classes.PoliceOfficer policeofficer = new Classes.PoliceOfficer("Jane Hope",32);

			firefigther.PensionAmount = 5000;
			firefigther.DriveToPlaceOfInterest();

			policeofficer.PensionAmount = 5500;
			policeofficer.HasEmergancy = true;
			policeofficer.DriveToPlaceOfInterest();

			PrintNameAndAge(firefigther);
			PrintPensionAmount(firefigther);

			PrintNameAndAge(policeofficer);
			PrintPensionAmount(policeofficer);
		}

		static void PrintNameAndAge(Interfaces.IPerson person){
				Console.WriteLine("Name: "+person.Name);
				Console.WriteLine("Age: "+person.Age);
		}

		static void PrintPensionAmount(Classes.PublicServant servant){
			if(servant is Classes.Firefigther){
				Console.WriteLine("Pension of firefigther: "+servant.PensionAmount);
			}else if(servant is Classes.PoliceOfficer){
					Console.WriteLine("Penison of Police officer:"+servant.PensionAmount);
			}
		}
	}


}

