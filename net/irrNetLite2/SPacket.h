#ifndef NET_PACKET_H
#define NET_PACKET_H

#include <irrTypes.h>
#include <vector3d.h>
#include <irrArray.h>
#include <irrString.h>
#include <string>

namespace irr
{
namespace net
{

/// An SOutPacket class, used for sending packets.
class SOutPacket
{
	public:
		SOutPacket();
		SOutPacket(const c8* buff,const u32 buff_size);

		/// Adds data to the packet.
		SOutPacket& operator << (const c8  data);
		/// Adds data to the packet.
		SOutPacket& operator << (const u16 data);
		/// Adds data to the packet.
		SOutPacket& operator << (const u32 data);
		/// Adds data to the packet.
		SOutPacket& operator << (const u8  data);
		/// Adds data to the packet.
		SOutPacket& operator << (const s16 data);
		/// Adds data to the packet.
		SOutPacket& operator << (const s32 data);
		/// Adds data to the packet.
		SOutPacket& operator << (const f32 data);
		/// Adds data to the packet.
		SOutPacket& operator << (const f64 data);
		/// Adds data to the packet.
		SOutPacket& operator << (const core::vector3df& data);
		/// Adds data to the packet.
		SOutPacket& operator << (const c8* string);
		/// Adds data to the packet.
		SOutPacket& operator << (const core::stringc& string);
		/// Adds data to the packet.
		SOutPacket& operator << (const std::string& string);
		/// Adds data to the packet.
		SOutPacket& operator << (const core::stringw& string);

		/// Clears the data in the packet. (Resets the write position)
		void clearData();
		
		/// Gets the data in the packet.
		c8* getData();

		/// Returns the size in bytes of the packet.
		u32 getSize(); 

		/// Compresses the packet using zlib compression.
		void compressPacket();

		/// Decompresses the packet using zlib decompression.
		void deCompressPacket();

		/// Encrypts a packet using AES encryption.
		void encryptPacket(const c8 key[16]);

		/// Decrypts a packet using AES decryption.
		void decryptPacket(const c8 key[16]);
  private:
		void enlargeBuffer(const u32 size);
		core::array<c8> buff;
};

/// An SInPacket class, used for handling recieved packets.
class SInPacket
{
  public:
		SInPacket(const c8* buff, const u32 size);
		
		void setNewData(const c8* buffer, const u32 size);

		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (c8& data);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (u16& data);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (u32& data);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (u8& data);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (s16& data);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (s32& data);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (f32& data);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (f64& data);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (core::vector3df& data);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (char* string);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (core::stringc& string);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (std::string& string);
		/// Gets the next item in the packet based on the size of the variable.
		void operator >> (core::stringw& string);

		/// Gets the data in the packet.
		c8* getData();

		/// Resets the read position.
		void resetPos();

		/// Returns the player ID of the player that sent this packet. (Only for servers)
		u16 getPlayerId() const;
		
		// Used internally by irrNetLite to set the player ID.
		void setPlayerId(u16 playernumber);

		/// Compresses the packet using zlib compression.
		void compressPacket();

		/// Decompresses the packet using zlib decompression.
		void deCompressPacket();

		/// Encrypts a packet using AES encryption.
		void encryptPacket(const c8 key[16]);

		/// Decrypts a packet using AES decryption.
		void decryptPacket(const c8 key[16]);
	private:
		u32 pos;
		core::array<c8> buff;
		u16 playerid;
};

} // Close Net Namespace
} // Close Irr namespace

#endif
