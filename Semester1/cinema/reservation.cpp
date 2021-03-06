
struct movie
{
    string normal[8][7];
    string vip[2][7];
};

class seats {
	private:
		ux UX;
		sysObjects sys;
		security sec;
		receipt rec;
	public:
		void displayMovies(string m) {

			ifstream myMovies("MoviesInfo.txt");
			while(!myMovies.eof()) {
				string tmpString, tmpString2;
				getline(myMovies, tmpString2);
				getline(myMovies, tmpString);
				getline(myMovies, tmpString);
				if(tmpString2[0]>0)
					cout << "At " << tmpString << ": " << tmpString2 << "\n";
			}
			cout << "\n";
		}
		bool checkUser(string userName) {
			sec.encryptDecrypt("pInfo.txt");
			ifstream myFile("pInfo.txt");
			while(!myFile.eof()) {
				string temp; myFile >> temp;
				if(temp==userName) {
					sec.encryptDecrypt("pInfo.txt");
					return true;
				}
			}
			sec.encryptDecrypt("pInfo.txt");
			return false;
		}
			
		string getHisUserName() {
			cout << "\nPlease Enter your username: ";
			string userName; cin >> userName;
			if(!checkUser(userName)) {
				cout << "You are not registered, please register a new account\n";
				userName = "-1";
			}
			return userName;
		}
		string ChooseMovie()
		{
			sys.clearScreen();
			UX.welcome();
			string movie;
			cout <<"The available movies are: \n\n";
			displayMovies("MovieInfo.txt");
			cout <<"What movie you want to book? ";
			cin.ignore();
			getline(cin,movie);
			return movie;
		}

		int afterReserve() {
			/*
			 * Receipt stuff here
			 */
			int inputToReturn;
			cout << "\nPress 1 to go back to the main menu\n";
			cin >> inputToReturn;
			return -1*inputToReturn;
		}
		int searchMovie (string film[], string m)
		{
			for (int i = 0; i<20; i++)
			{
				if (film[i]==m)
				{
				return i;
				break;
				}
			}
			  return -1;
		}
		string ChooseSeat ()
		{
			string seat;
			cout <<"Choose a seat for the movie: ";
			cin >> seat;
			return seat;
		}
		void displaySeats(movie arr[] , int count)
		{
			
			cout <<"\nThese are the available seats for this movie\n"<<endl;
			cout <<"--------------------------"<<endl;
			cout <<"     Normal Seats (15$) "<<endl;

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					cout <<arr[count].normal[i][j]<<"  ";
				}
				cout <<endl;
			}
			cout <<"--------------------------"<<endl;
			cout <<"      VIP Seats (25$)"<<endl;
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					cout <<arr[count].vip[i][j]<<"  ";
				}
			}
				cout <<"\n\n";
			
		}

		void searchSeat (movie arr[], int count, string s)
		{
			int c = 0;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (arr[count].normal[i][j] == s )
					{
						 cout << "\nThis Normal Seat is available "<<endl;
						 arr[count].normal [i][j] = "XX";
						 c++;
					}  
				}
			}
			int b = 0;
			 for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (arr[count].vip[i][j] == s)
					{
						 cout << "\nThis VIP Seat is available "<<endl;
						 arr[count].vip[i][j]="XX";
						 b++;
					}  
				}
			}
			
			if (b==0 && c==0) {
				cout <<"\nSorry! Seat is unavailable "<<endl;
				string newSeat = ChooseSeat();
				searchSeat(arr, count, newSeat);
			}
		}
		void modifySeats (string movieRegister, string film[], movie arr[])
		{
			ofstream myfile (movieRegister);
			 for (int i = 0; i<20; i++)
			{
				myfile <<film[i]<<'\n';
				for (int j = 0; j<8; j++)
				{
					for (int m = 0; m<7; m++)
					{
						myfile << arr[i].normal[j][m]<<" ";
				}
				}
				myfile <<endl;
				for (int j = 0; j<2; j++)
				{
					for (int m = 0; m<7; m++)
					{
						myfile << arr[i].vip[j][m]<<" ";
				}
				}
				myfile<<endl;
			}
			 myfile.close();
		}
		string getMyTiming(string m) {
			ifstream movieTime("MoviesInfo.txt");
			string timing;
			while(!movieTime.eof()) {
				getline(movieTime,timing);
				if(timing==m) {
					getline(movieTime,timing);
					getline(movieTime,timing);
					return timing;
				}
			}
			return "NULL";
		}
		int movieRegistration (string movieRegister)
		{
			string line;
			fstream file;
			file.open(movieRegister, ios::out | ios::in);

			string film[100];
			movie *arr = new movie [100];
		 
			for (int i = 0; i<20; i++)
			{
				getline(file, line);
				film[i] = line;
				for(int j = 0; j<2; j++) 
				getline(file, line);
			}
			
			file.clear();
			file.seekg(0);
			getline(file, line);
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j<8; j++)
					for (int m = 0; m<7; m++)
						file >> arr[i].normal[j][m];
				getline(file, line);
				 for (int j = 0; j<2; j++)
					for (int m = 0; m<7; m++)
						file >> arr[i].vip[j][m];
				for (int n = 0; n<2; n++)
				getline(file, line);
			}
			file.clear();
			file.seekg(0);

			string m = ChooseMovie();
			int count = searchMovie (film, m);
			if(count == -1) {
				cout << "\nUnfortunately, this movie is not available\n";
				sleep(1);
				cout << "\nTaking you back to the previous menu...\n";
				sleep(2);
				m=ChooseMovie();
			}
			
			displaySeats(arr, count);
			string s = ChooseSeat ();
			searchSeat (arr, count, s);
			file.close();
			string buyerName = getHisUserName();
			if(buyerName=="-1")
				return -3;
			string timO = getMyTiming(m);
			bool is_vip=false;
			if(s[0]=='I' || s[0]=='J')
				is_vip=true;
			cout << "\n";
			rec.receiptDo(buyerName, m, s, timO, is_vip);
			modifySeats (movieRegister, film, arr);
			return afterReserve();
		}

};
