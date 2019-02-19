/***************************************************************************************
 ***                                                                                 ***
 ***  Copyright (c) 2018, Lucid Vision Labs, Inc.                                    ***
 ***                                                                                 ***
 ***  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     ***
 ***  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       ***
 ***  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    ***
 ***  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         ***
 ***  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  ***
 ***  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  ***
 ***  SOFTWARE.                                                                      ***
 ***                                                                                 ***
 ***************************************************************************************/      
#pragma once
#include <string>

namespace Arena
{
	/**
	 * @class InterfaceInfo
	 *
	 * Device information objects contain device discovery information used to
	 * find, filter, and create devices.
	 *
	 * A list of device information objects is retrieved and maintained in the
	 * system (Arena::ISystem). A device information object provides a device's
	 * discovery information: 
	 *  - model and vendor names 
	 *  - serial number 
	 *  - IP and MAC addresses 
	 *  - subnet mask
	 *
	 * Discovery information is acquired prior to device creation and used
	 * primarily to filter and find specific devices. A std::vector of
	 * Arena::InterfaceInfo objects is retrieved from the system (via
	 * Arena::ISystem::GetDevices). They are then individually passed back to the
	 * system to create devices (via Arena::ISystem::CreateDevice).
	 *
	 * The list of DeviceInfos is returned as a std::vector in order to make use
	 * of STL filter and search tools. The following code snippet demonstrates
	 * searching for a device with a specific serial number:
	 *
	 * \code{.cpp}
	 * 	// searching for a specific device
	 * 	{
	 * 		GenICam::gcstring serialToFind = "12345";
	 * 		std::vector<Arena::InterfaceInfo> devs = pSystem->GetDevices();
	 * 		
	 * 		auto it = std::find_if(begin(devs), end(devs), [&serialToFind](Arena::InterfaceInfo deviceInfo)
	 * 		{
	 * 			return deviceInfo.SerialNumber() == serialToFind;
	 * 		});
	 * 	}
	 * \endcode
	 *
	 * @see 
	 *  - Arena::ISystem 
	 *  - Arena::InterfaceInfo
	 */
	class ARENA_API InterfaceInfo
	{
	public:

		/**
		 * @fn virtual uint32_t IpAddress()
		 *
		 * @return 
		 *  - Type: uint32_t 
		 *  - IP address of the device as an integer
		 *
		 * <B> IpAddress </B> gets the IP address of a device on the network,
		 * returning it as its raw integer value.
		 *
		 * The GigE Vision specification only allows for IPv4 IP addresses. The IP
		 * address is represented by the lower 32 bits of the integer returned. Both
		 * <B> IpAddress </B> and <B> IpAddressStr </B> represent the same IP
		 * address. Where <B> IpAddress </B> returns the value in its raw integer
		 * format, <B> IpAddressStr </B> returns it as a more human-readable string: 
		 *  - <B> IpAddress </B>: 0xA9FE0101 
		 *  - <B> IpAddressStr </B>: 169.254.1.1
		 *
		 * A device may have its IP address, subnet mask, and default gateway
		 * assigned by LLA or DHCP, set as persistent, or temporarily forced. They
		 * can be checked through the main node map (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPAddress', 'GevCurrentSubnetMask',
		 * 'GevCurrentDefaultGateway').
		 *
		 * DHCP (Arena::IDevice::GetNodeMap, 'GevCurrentIPConfigurationDHCP') and IP
		 * persistence (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPConfigurationPersistentIP') can be enabled/disabled through
		 * the node map. If both are enabled, a device will default to its persistent
		 * IP settings. If neither, it will default to LLA
		 * (Arena::IDevice::GetNodeMap, 'GevCurrentIPConfigurationLLA'), which cannot
		 * be disabled.
		 *
		 * In order to configure a device to use a persistent IP configuration, not
		 * only must IP persistence be enabled (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPConfigurationPersistentIP'), but the IP address
		 * (Arena::IDevice::GetNodeMap, 'GevPersistentIPAddress'), subnet mask
		 * (Arena::IDevice::GetNodeMap, 'GevPersistentSubnetMask'), and default
		 * gateway (Arena::IDevice::GetNodeMap, 'GevPersistentDefaultGateway') must
		 * be set.
		 *
		 * Forcing an IP (Arena::IDevice::ForceIP) temporarily changes an IP address,
		 * subnet mask, and default gateway of a device. A forced IP configuration
		 * will reset on a device reboot (Arena::IDevice::GetNodeMap, 'DeviceReset').
		 *
		 * The IP address returned by this getter is the same as the one received in
		 * the GigE Vision discovery acknowledgement.
		 *
		 * @warning 
		 *  - Represents same information as Arena::InterfaceInfo::IpAddressStr 
		 *  - A persistent IP may be quicker to enumerate than DHCP, which should be
		 *    faster than LLA
		 *
		 * @see 
		 *  - Arena::IDevice::GetNodeMap 
		 *  - Arena::IDevice::ForceIP 
		 *  - Arena::InterfaceInfo::IpAddressStr
		 */
		virtual uint32_t IpAddress();

		/**
		 * @fn virtual GenICam::gcstring IpAddressStr()
		 *
		 * @return 
		 *  - Type: GenICam::gcstring 
		 *  - IP address of the device as a string
		 *
		 * <B> IpAddressStr </B> gets the IP address of a device on the network,
		 * returning it as a string.
		 *
		 * The GigE Vision specification only allows for IPv4 IP addresses. Both <B>
		 * IpAddress </B> and <B> IpAddressStr </B> represent the same IP address.
		 * Where <B> IpAddress </B> returns the value in its raw integer format, <B>
		 * IpAddressStr </B> returns it as a more human-readable string: 
		 *  - <B> IpAddress </B>: 0xA9FE0101 
		 *  - <B> IpAddressStr </B>: 169.254.1.1
		 *
		 * A device may have its IP address, subnet mask, and default gateway
		 * assigned by LLA or DHCP, set as persistent, or temporarily forced. They
		 * can be checked through the main node map (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPAddress', 'GevCurrentSubnetMask',
		 * 'GevCurrentDefaultGateway').
		 *
		 * DHCP (Arena::IDevice::GetNodeMap, 'GevCurrentIPConfigurationDHCP') and IP
		 * persistence (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPConfigurationPersistentIP') can be enabled/disabled through
		 * the node map. If both are enabled, a device will default to its persistent
		 * IP settings. If neither, it will default to LLA
		 * (Arena::IDevice::GetNodeMap, 'GevCurrentIPConfigurationLLA'), which cannot
		 * be disabled.
		 *
		 * In order to configure a device to use a persistent IP configuration, not
		 * only must IP persistence be enabled (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPConfigurationPersistentIP'), but the IP address
		 * (Arena::IDevice::GetNodeMap, 'GevPersistentIPAddress'), subnet mask
		 * (Arena::IDevice::GetNodeMap, 'GevPersistentSubnetMask'), and default
		 * gateway (Arena::IDevice::GetNodeMap, 'GevPersistentDefaultGateway') must
		 * be set.
		 *
		 * Forcing an IP (Arena::IDevice::ForceIP) temporarily changes an IP address,
		 * subnet mask, and default gateway of a device. A forced IP configuration
		 * will reset on a device reboot (Arena::IDevice::GetNodeMap, 'DeviceReset').
		 *
		 * The IP address returned by this getter is the same as the one received in
		 * the GigE Vision discovery acknowledgement, but as a dot-separated string.
		 *
		 * @warning 
		 *  - Represents same information as Arena::InterfaceInfo::IpAddress 
		 *  - A persistent IP may be quicker to enumerate than DHCP, which should be
		 *    faster than LLA
		 *
		 * @see 
		 *  - Arena::IDevice::GetNodeMap 
		 *  - Arena::IDevice::ForceIP 
		 *  - Arena::InterfaceInfo::IpAddress
		 */
		virtual GenICam::gcstring IpAddressStr();

		/**
		 * @fn virtual uint32_t SubnetMask()
		 *
		 * @return 
		 *  - Type: uint32_t 
		 *  - Subnet mask of the device as an integer
		 *
		 * <B> SubnetMask </B> gets the subnet mask of a device on the network,
		 * returning it as its raw integer value.
		 *
		 * The GigE Vision specification only allows for IPv4 subnet masks. The
		 * subnet mask is represented by the lower 32 bits of the integer returned.
		 * Both <B> SubnetMask </B> and <B> SubnetMaskStr </B> represent the same
		 * subnet mask. Where <B> SubnetMask </B> returns the value in its raw
		 * integer format, <B> SubnetMaskStr </B> returns it as a more human-readable
		 * string: 
		 *  - <B> SubnetMask </B>: 0xFFFF0000 
		 *  - <B> SubnetMaskStr </B>: 255.255.0.0
		 *
		 * A device may have its IP address, subnet mask, and default gateway
		 * assigned by LLA or DHCP, set as persistent, or temporarily forced. They
		 * can be checked through the main node map (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPAddress', 'GevCurrentSubnetMask',
		 * 'GevCurrentDefaultGateway').
		 *
		 * DHCP (Arena::IDevice::GetNodeMap, 'GevCurrentIPConfigurationDHCP') and IP
		 * persistence (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPConfigurationPersistentIP') can be enabled/disabled through
		 * the node map. If both are enabled, a device will default to its persistent
		 * IP settings. If neither, it will default to LLA
		 * (Arena::IDevice::GetNodeMap, 'GevCurrentIPConfigurationLLA'), which cannot
		 * be disabled.
		 *
		 * In order to configure a device to use a persistent IP configuration, not
		 * only must IP persistence be enabled (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPConfigurationPersistentIP'), but the IP address
		 * (Arena::IDevice::GetNodeMap, 'GevPersistentIPAddress'), subnet mask
		 * (Arena::IDevice::GetNodeMap, 'GevPersistentSubnetMask'), and default
		 * gateway (Arena::IDevice::GetNodeMap, 'GevPersistentDefaultGateway') must
		 * be set.
		 *
		 * Forcing an IP (Arena::IDevice::ForceIP) temporarily changes an IP address,
		 * subnet mask, and default gateway of a device. A forced IP configuration
		 * will reset on a device reboot (Arena::IDevice::GetNodeMap, 'DeviceReset').
		 *
		 * The subnet mask returned by this getter is the same as the one received in
		 * the GigE Vision discovery acknowledgement.
		 *
		 * @warning 
		 *  - Represents same information as Arena::InterfaceInfo::SubnetMaskStr 
		 *  - A persistent IP may be quicker to enumerate than DHCP, which should be
		 *    faster than LLA
		 *
		 * @see 
		 *  - Arena::IDevice::GetNodeMap 
		 *  - Arena::IDevice::ForceIP 
		 *  - Arena::InterfaceInfo::SubnetMaskStr
		 */
		virtual uint32_t SubnetMask();

		/**
		 * @fn virtual GenICam::gcstring SubnetMaskStr()
		 *
		 * @return 
		 *  - Type: GenICam::gcstring 
		 *  - Subnet mask of the device as a string
		 *
		 * <B> SubnetMaskStr </B> gets the subnet mask of a device on the network,
		 * returning it as a string.
		 *
		 * The GigE Vision specification only allows for IPv4 IP addresses. Both <B>
		 * SubnetMask </B> and <B> SubnetMaskStr </B> represent the same subnet mask.
		 * Where <B> SubnetMask </B> returns the value in its raw integer format, <B>
		 * SubnetMaskStr </B> returns it as a more human-readable string: 
		 *  - <B> SubnetMask </B>: 0xFFFF0000 
		 *  - <B> SUbnetMaskStr </B>: 255.255.0.0
		 *
		 * A device may have its IP address, subnet mask, and default gateway
		 * assigned by LLA or DHCP, set as persistent, or temporarily forced. They
		 * can be checked through the main node map (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPAddress', 'GevCurrentSubnetMask',
		 * 'GevCurrentDefaultGateway').
		 *
		 * DHCP (Arena::IDevice::GetNodeMap, 'GevCurrentIPConfigurationDHCP') and IP
		 * persistence (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPConfigurationPersistentIP') can be enabled/disabled through
		 * the node map. If both are enabled, a device will default to its persistent
		 * IP settings. If neither, it will default to LLA
		 * (Arena::IDevice::GetNodeMap, 'GevCurrentIPConfigurationLLA'), which cannot
		 * be disabled.
		 *
		 * In order to configure a device to use a persistent IP configuration, not
		 * only must IP persistence be enabled (Arena::IDevice::GetNodeMap,
		 * 'GevCurrentIPConfigurationPersistentIP'), but the IP address
		 * (Arena::IDevice::GetNodeMap, 'GevPersistentIPAddress'), subnet mask
		 * (Arena::IDevice::GetNodeMap, 'GevPersistentSubnetMask'), and default
		 * gateway (Arena::IDevice::GetNodeMap, 'GevPersistentDefaultGateway') must
		 * be set.
		 *
		 * Forcing an IP (Arena::IDevice::ForceIP) temporarily changes an IP address,
		 * subnet mask, and default gateway of a device. A forced IP configuration
		 * will reset on a device reboot (Arena::IDevice::GetNodeMap, 'DeviceReset').
		 *
		 * The subnet mask returned by this getter is the same as the one received in
		 * the GigE Vision discovery acknowledgement, but as a dot-separated string.
		 *
		 * @warning 
		 *  - Represents same information as Arena::InterfaceInfo::SubnetMask 
		 *  - A persistent IP may be quicker to enumerate than DHCP, which should be
		 *    faster than LLA
		 *
		 * @see 
		 *  - Arena::IDevice::GetNodeMap 
		 *  - Arena::IDevice::ForceIP 
		 *  - Arena::InterfaceInfo::SubnetMask
		 */
		virtual GenICam::gcstring SubnetMaskStr();

		/**
		 * @fn virtual uint64_t MacAddress()
		 *
		 * @return 
		 *  - Type: uint64_t 
		 *  - MAC address of the device as an integer
		 *
		 * <B> MacAddress </B> gets the MAC address of a device on the network,
		 * returning it as its raw integer value.
		 *
		 * Both <B> MacAddress </B> and <B> MacAddressStr </B> represent the same MAC
		 * address. Where <B> MacAddress </B> returns the value in its raw integer
		 * format, <B> MacAddressStr </B> returns it as a more human-readable string:
		 *  - <B> MacAddress </B>: 0x1C0FAF010101 
		 *  - <B> MacAddressStr </B>: 1C:0F:AF:01:01:01
		 *
		 * The MAC address returned by this getter is the same as the one received in
		 * the GigE Vision discovery acknowledgement.
		 *
		 * @warning 
		 *  - Represents same information as Arena::InterfaceInfo::MacAddressStr
		 *
		 * @see 
		 *  - Arena::InterfaceInfo::MacAddressStr
		 */
		virtual uint64_t MacAddress();

		/**
		 * @fn virtual GenICam::gcstring MacAddressStr()
		 *
		 * @return 
		 *  - Type: GenICam::gcstring 
		 *  - MAC address of the device as a string
		 *
		 * <B> MacAddressStr </B> gets the MAC address of a device on the network,
		 * returning it as a string.
		 *
		 * Both <B> MacAddress </B> and <B> MacAddressStr </B> represent the same MAC
		 * address. Where <B> MacAddress </B> returns the value in its raw integer
		 * format, <B> MacAddressStr </B> returns it as a more human-readable string:
		 *  - <B> MacAddress </B>: 0x1C0FAF010101 
		 *  - <B> MacAddressStr </B>: 1C:0F:AF:01:01:01
		 *
		 * The MAC address returned by this getter is the same as the one received in
		 * the GigE Vision discovery acknowledgement.
		 *
		 * @warning 
		 *  - Represents same information as Arena::InterfaceInfo::MacAddress
		 *
		 * @see 
		 *  - Arena::InterfaceInfo::MacAddress
		 */
		virtual GenICam::gcstring MacAddressStr();

		/**
		 * @fn InterfaceInfo()
		 *
		 * An empty constructor
		 *
		 * @warning 
		 *  - Does not sufficiently initialize InterfaceInfo
		 */
		InterfaceInfo();

		/**
		 * @fn InterfaceInfo(const InterfaceInfo& deviceInfo)
		 *
		 * A copy constructor
		 *
		 * @param deviceInfo
		 *  - Type: const InterfaceInfo& 
		 *  - Device information object to copy
		 */
		InterfaceInfo(const InterfaceInfo& deviceInfo);

		/**
		 * @fn virtual ~InterfaceInfo()
		 *
		 * A destructor
		 */
		virtual ~InterfaceInfo();

		/**
		 * @fn virtual InterfaceInfo& operator=(InterfaceInfo deviceInfo)
		 *
		 * A copy assignment operator
		 *
		 * @param deviceInfo
		 *  - Type: InterfaceInfo 
		 *  - Device information object to copy
		 *
		 * @return 
		 *  - Type: InterfaceInfo& 
		 *  - Copied device information object
		 */
		virtual InterfaceInfo& operator=(InterfaceInfo deviceInfo);

	protected:

		friend class System;
		void* m_pData;
	};
} // namespace Arena
