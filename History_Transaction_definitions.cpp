#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//
Transaction::Transaction( std::string ticker_symbol, unsigned int day_date, unsigned int month_date,
unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount
){
  //assign the parameters
  symbol=ticker_symbol;
  day=day_date;
  month=month_date;
  year=year_date;

  if(buy_sell_trans){
    trans_type="Buy";
  }
  else{
    trans_type="Sell";
  }
  shares=number_shares;
  amount=trans_amount;
  trans_id=assigned_trans_id;
  assigned_trans_id++;
  p_next = nullptr;



  



 
}





// Destructor
// TASK 1
//
Transaction::~Transaction(){
  p_next = nullptr;

}


// Overloaded < operator.
// TASK 2
//
bool Transaction::operator<( Transaction const &other ){
  if(year<other.year){
    return true;
      }
      else if((year==other.year) && (month<other.month)){
        return true;
      }
      else if((year==other.year) && (month==other.month) && (day<other.day)){
        return true;
      }
    
    else if((year==other.year)&&(month==other.month)&&(day==other.day)){
    if(trans_id>other.trans_id){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//



// Constructor
// TASK 3
//
History::History(){
  p_head = 0;
}

// Destructor
// TASK 3
//
History::~History(){
  Transaction *runner=p_head;
  // if(p_head==nullptr){
  //   delete p_head;
  // }

  while(p_head!=nullptr){
    p_head=p_head->get_next();
    delete runner;
    runner=nullptr;
    runner=p_head;
  }


}



// read_history(...): Read the transaction history from file.
// TASK 4
//
void History::read_history(){

   ece150::open_file();

   while(ece150::next_trans_entry()){
    Transaction *transaction{new Transaction(ece150::get_trans_symbol(),ece150::get_trans_day(),
    ece150::get_trans_month(),ece150::get_trans_year(),ece150::get_trans_type(),ece150::get_trans_shares(),
    ece150::get_trans_amount())};

    this->insert(transaction);

   }
   ece150::close_file();

}

// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert( Transaction *p_new_trans ){
  Transaction *runner=p_head;

  if(p_head==nullptr){
    p_head=p_new_trans;
  }
else{
  runner = p_head;
  while(runner->get_next()!=nullptr){
    runner=runner->get_next();

  }
  runner->set_next(p_new_trans);
}
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date(){

  
  // if(p_head!=nullptr){
  //   Transaction *new_head{p_head};
  //   p_head=p_head->get_next();

  //   while(p_head!=nullptr&& p_head<new_head){
  //     Transaction *temp=p_head;
  //     p_head=temp->get_next();
  //     temp->get_next()==new_head;
  //     new_head->get_next()==p_head; 
  //     new_head=temp;

  //   }
     
  // }
  int swapped{0};

  while(swapped == 0){
   

  Transaction *new_head=nullptr;
  Transaction *current=p_head;
  Transaction *nxt=nullptr;

  while(current->get_next()!=nullptr){

    if(*current->get_next()<*current){

      if(new_head==nullptr){
        nxt = current->get_next();
        current->set_next(nxt->get_next());
        nxt->set_next(current);
        new_head=nxt;
        p_head=nxt;
        swapped++;
      }

      else{
        nxt = current->get_next();
        new_head->set_next(nxt);
        current->set_next(nxt->get_next());
        nxt->set_next(current);
        new_head=nxt;
        swapped++;
      } 
    }

    else{
      new_head=current;
      current=current->get_next();
      
    }
     
  }
  if(swapped==0){
    break;
  }
  else{
    swapped=0;
    new_head=nullptr;
    nxt=nullptr;
    current=p_head;


  }
}
}




// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History::update_acb_cgl(){
  Transaction *transit;
  transit=p_head;
  double acb=transit->get_acb();
  unsigned int share_balance=transit->get_share_balance();
  double acb_per_share=acb/share_balance;
  double cgl=transit->get_cgl();
  

  transit->set_acb(acb);
  transit->set_acb_per_share(acb_per_share);
  transit->set_share_balance(share_balance);
  transit->set_cgl(cgl);
  
while( transit->get_next() != nullptr){
  transit = transit -> get_next();
  //When it is Buy
  if(transit->get_trans_type()){
    acb+=transit->get_amount();
    share_balance+=transit->get_share_balance();
    acb_per_share=(acb/share_balance);

    transit -> set_acb (acb);
    transit -> set_acb_per_share(acb_per_share);
    transit -> set_share_balance(share_balance);
  }

  //When it is Sell
  else{
    acb-=(transit->get_shares()*acb_per_share);
    share_balance-=transit->get_shares();
    // acb_per_share=(acb/share_balance);
    cgl=(transit->get_amount())-(transit->get_shares()*acb_per_share);

    transit -> set_acb (acb);
    transit -> set_acb_per_share(acb_per_share);
    transit -> set_share_balance(share_balance);
    transit -> set_cgl(cgl);
  }

}



  

}



// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl( unsigned int year ){
  Transaction *compute = p_head;
  double sum{0};
  while(compute != nullptr){
    
    if( compute -> get_year() == year){
      sum=sum+compute->get_cgl();
    }
    compute=compute->get_next();
  }
  return sum;
}




// print() Print the transaction history.
//TASK 9
//
void History::print(){

  std::cout<<"========== BEGIN TRANSACTION HISTORY ============"<<std::endl;
  Transaction *new_runner = p_head;
  while(new_runner!=nullptr){
    new_runner -> print();
    new_runner = new_runner -> get_next();
  }
  std::cout<<"========== END TRANSACTION HISTORY ============"<<std::endl;


}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
