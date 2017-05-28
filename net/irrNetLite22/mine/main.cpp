/*
Welcome to the simple, introductory tutorial for irrNetLite. This will show you the
very basics of setting up a client and server, and sending and receiving packets.
Because irrNetLite is so easy to use, I think you will not find many actual lines of
code in this example, rather most of it is documentation.

For much more sophisticated use of irrNetLite, I recommend taking a look in the
examples subdirectory.
*/
#include <irrNet.h>
#include <iostream>
bool connected,doit,login = false;

// irrNetLite resides within the irr::net:: namespace, therefore,
// we use "using namespace irr" here to simplify things.
// Alternatively you can add "using namespace net" after
// this so that net:: doesn't have to be used either.
using namespace irr;

// These pragmas are for MSVC users, they ease the linking of librarys.
// "ws2_32.lib" is part of the Windows Platform SDK and must be linked
// in when compiling on windows. On linux/mac machines, these pragmas
// will simply be ignored, and the linking to irrNetLite static lib
// should be performed by a makefile.
#pragma comment(lib, "irrNetLite.lib")
#pragma comment(lib, "ws2_32.lib")


// You must derive a class from INetCallback and override the
// "handlePacket" method. When a packet is received it will be
// passed to this function, and you may dissect it as you wish.
// If this is the server you may retrieve the player ID using
// packet.getPlayerId().
    net::INetManager* netManager;
	net::SOutPacket packet2;

class ClientNetCallback : public net::INetCallback
{
public:
	virtual void handlePacket(net::SInPacket& packet)
	{
		// irrNetLite encryption is very easy to use! Just pass
		// a 16-byte (128-bit) string to encryptPacket/decryptPacket
		// to encrypt/decrypt a packet respectively. Do not try to
		// decrypt an un-encrypted packet or read from an encrypted
		// packet without decrypting it first or bad things will happen!
	//	packet.decryptPacket("hushthisissecret");

		// irrNetLite compression is even easier! The ZLib library is used
		// here, just call compressPacket/decompressPacket to
		// compress/decompress a packet. Again, do not try to decompress
		// an un-compressed packet or read from a compressed packet without
		// decompressing it! Another thing to keep in mind is that you should
		// decompress and decrypt in the correct order. If you compressed a file
		// and then encrypted it when it was sent, you must decrypt it first
		// before trying to decompress it, same goes for the other order.
		//packet.deCompressPacket();
        printf("handleing the Packet\n");
			core::stringc str;
		packet >> str;

        if ( str == "first" ){  //great were connected
                std::cout << "we got handshake2" << str.c_str() << "\n"<< std::endl;
                connected=true;
                	//		    	packet2 << "actPack2";

        }
        if ( str == "second" ){  // this would be the login data
                std::cout << "hit second connected! \n" << str.c_str() << "\n"<< std::endl;
           //     connected=true;
                doit=true;
                	//		    	packet2 << "actPack2";
        }
        if ( str == "actPack2"){
               std::cout << "AUTHORIZED!!" << str.c_str() << "\n" << std::endl;
               login=true;
               connected=true;
//  if (!login){  // if has not logged in yet then send hands
        }else{
                std::cout << "other " << str.c_str() << "\n" <<std::endl;
	}
        }
};

//net::SOutPacket packet;
// Ok, lets go from the start, int main()
int main()
{

		// Create an irrNet client, in this example we will just connect to the localhost
		// address ("127.0.0.1"), which basically means we are connecting to the same
		// computer the client is on. Note that we just pass a value of 0 as our
		// INetCallback, because the client in this example does no need to handle any
		// packets. You can safely pass a value of 0 if this is the case.
		ClientNetCallback* clientCallback = new ClientNetCallback();
		netManager = net::createIrrNetClient(clientCallback, "127.0.0.1");		// Here comes the fun part, while the client is connected we update the netManager
		// and ask it to wait 1 second (1000 milliseconds) for new packets to arrive before
		// returning. Since the client in this example doesn't actually receive any packets,
		// the only purpose of the update call is to leave a 1 second interval between each
		// packet we send.
       //     netManager->update(1000); //update(delay);
       while (1){
		if(netManager->getConnectionStatus() != net::EICS_FAILED)
		{
        if (login==true){printf("YAAAAAAAAAAAAAAAAAAAAAAAY");}
			// To send a packet, first you create an SOutPacket object.
			net::SOutPacket packet;
//			// Then you can use the streaming operator << to add new data to it.
			if (connected){  // check if already logged in send reset to server
        if (doit==true){ // send credentials if connected
//			netManager->sendOutPacket(packet2);
		packet << "userLogin";
			printf("sending userLogin");
			netManager->sendOutPacket(packet);
//
			}else{
			printf ("not connected-connecting \n");
						packet << "second";
                        netManager->sendOutPacket(packet);
//                //        iReturn = 1; //

			}
			}
			            netManager->update(1000); //update(delay);
			}

		}
		// When the connection disconnects (Or fails), the loop will terminate.
		// Remember to delete the netManager so that all the low level networking
		// stuff is cleaned up properly.
		delete netManager;

	// And we're done, return 0 and make like a tree.
	return 0;
}
