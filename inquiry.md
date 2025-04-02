## What did you learn from this assignment?
I learnt alot on how to use smart pointers, how to use inheritance, 
found making a deep copy of the board quite difficult to understand and to implement. Using shared pointers in a bigger project is also something I learnt
about. I also learnt how to use dynamic pointer cast to check if something is 
what you want it to be as, as opposed to using another cast such as static
pointer cast. I also was able to make use of lambda functions too.


## What was most difficult to do in this assignment?
I found it very difficult to impement the deep copy of the board, implementing the 
second AI was a bit difficult to since there was a lot to think about
Furthermore it was quite tough to get all the moves exactly right and 
to test, I tested using a lot of print statements which worked but working
out exactly how everything should be was a bit difficult. I still find it 
quite difficult too to understand exactly when a reference should be used
instead of a direct assignment however I feel I learnt when to use references
and when to use direct assignments. I also had trouble as I read the tests
as 1 line of 64 characters when they really should have been 8 lines of 8 characters
each.

## The code relies on virtual functions. Could the code have been written without virtual functions?
Virtual functions allow for polymorphism which automatically invokes the right
derived class method, meaning that they inherit from a base class. So, yes it would technically be possible but you would need to check every piece's type with some sort of cast and then use a personal function to that type. Instead we can call virtual methods use overridden versions of the type. Which is far more easier.

## Could ChessPiece have been an abstract class?
Yes. We could set for example validMove to 0 so that it can't be instantiated itself. Then you could just have each individual derived class have it's own implementation. This would be less efficeint but would be possible.

## There was no separate unit test for each function in this assignment, instead you tested several functions at once with different boards. What are the benefits and drawbacks for this kind of testing compared to unit tests?
The problem with having no unittest is that it is difficult to identify what exactly
went wrong, which is a problem that I had. With unittests you avoid this problem
where certain issues may not be obvious,. You can test edge cases and isolated functions. However, correct implementation of the entire program, where the program behaves how you intend it to behave aren't capturable in unittests and therefore are far better in noticing implementation even if the individual functions might function properply.


## What is the problem with a diamond inheritance?
The problem with a diamond inheritance is that there can be ambugiuty by the compiler, if either the Rook's chesspiece copy or the Bishop's chesspiece copy is being reffered to. Also, the queen has technically then two separate copies from each part. By using then, virtual chesspieces for rook and the bishop you can only then have one instance of a Chesspiece making no ambiguity. If it wasn't virtual we'd have two copies of m_x, my_y and m_is_white and any other data members both defined in ChessPiece. 

## Did you encounter any problem with protected member variables and, if so, how did you solve them?
Well I did have some problems, but for instance I didn't have any specific problems with m_board being protected where the derived classes could access it. However, I felt better making it private and making getters and setters instead. It was a while since I did this part however I think in hindsight I could have kept it protected. I made the utfRepresentation and latin1Representation oublic as I use them in ChessBoard which is not a derived class of ChessPiece, so I suppose that counts as a problem I had with the protected member variables.