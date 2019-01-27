/* Copyright (C) 2019 Casper Meijn <casper@meijn.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SOAPUDPCLIENT_H
#define SOAPUDPCLIENT_H

#include <QObject>

class KDSoapHeaders;
class KDSoapMessage;
class QHostAddress;
class QNetworkDatagram;
class QUdpSocket;

class SoapUdpClient : public QObject
{
    Q_OBJECT
public:
    explicit SoapUdpClient(QObject *parent = nullptr);

    bool bind(quint16 port, const QHostAddress& ipv4MulticastGroup, const QHostAddress& ipv6MulticastGroup);

signals:
    void receivedMessage(const KDSoapMessage& replyMessage, const KDSoapHeaders& replyHeaders, const QHostAddress& senderAddress, quint16 senderPort);

public slots:
    bool sendMessage(const KDSoapMessage &replyMessage, const KDSoapHeaders &replyHeaders, const QHostAddress& host, quint16 port);

private slots:
    void readyRead();
    void recievedDatagram(const QNetworkDatagram& datagram);

private:
    QUdpSocket * m_socketIPv4;
    QUdpSocket * m_socketIPv6;
};

#endif // SOAPUDPCLIENT_H
