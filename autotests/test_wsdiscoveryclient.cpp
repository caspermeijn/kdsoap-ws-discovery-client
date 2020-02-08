#include <KDSoapClient/KDQName>
#include <QNetworkDatagram>
#include <QTest>
#include <QUdpSocket>
#include <QXmlStreamReader>
#include "wsdiscoveryclient.h"

class testWSDiscoveryClient: public QObject
{
    Q_OBJECT
private slots:
    void testSendProbe();
    
private:
    QByteArray zeroOutUuid(const QByteArray& original);
    QByteArray expectedSendProbeData();
    QByteArray formatXml(const QByteArray& original);
};

void testWSDiscoveryClient::testSendProbe() 
{
    QUdpSocket testSocket;
    bool rc = testSocket.bind(QHostAddress::Any, 3702, QAbstractSocket::ShareAddress);
    testSocket.joinMulticastGroup(QHostAddress("FF02::C"));
    QVERIFY(rc);

    WSDiscoveryClient discoveryClient;
    discoveryClient.start();

    KDQName type("tdn:NetworkVideoTransmitter");
    type.setNameSpace("http://www.onvif.org/ver10/network/wsdl");
    auto typeList = QList<KDQName>() << type;
    
    auto scopeList = QList<QUrl>() << QUrl("onvif://www.onvif.org/Profile/Streaming");
    
    discoveryClient.sendProbe(typeList, scopeList);

    QVERIFY(testSocket.hasPendingDatagrams());
    auto datagram = testSocket.receiveDatagram();
    auto zeroedDatagram = zeroOutUuid(datagram.data());
    QCOMPARE(formatXml(zeroedDatagram), formatXml(expectedSendProbeData()));
}


QByteArray testWSDiscoveryClient::expectedSendProbeData() {
    return QByteArray(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<soap:Envelope"
        "  xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\""
        "  xmlns:soap-enc=\"http://www.w3.org/2003/05/soap-encoding\""
        "  xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\""
        "  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
        "  xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
        "  xmlns:n1=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\">"
        "  <soap:Header>"
        "    <wsa:To>urn:schemas-xmlsoap-org:ws:2005:04:discovery</wsa:To>"
        "    <wsa:ReplyTo><wsa:Address>http://www.w3.org/2005/08/addressing/anonymous</wsa:Address></wsa:ReplyTo>"
        "    <wsa:Action>http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe</wsa:Action>"
        "    <wsa:MessageID>urn:uuid:00000000-0000-0000-0000-000000000000</wsa:MessageID>"
        "  </soap:Header>"
        "  <soap:Body>"
        "    <n1:Probe>"
        "      <n1:Types xmlns:tdn=\"http://www.onvif.org/ver10/network/wsdl\">tdn:NetworkVideoTransmitter</n1:Types>"
        "      <n1:Scopes>onvif://www.onvif.org/Profile/Streaming</n1:Scopes>"
        "    </n1:Probe>"
        "  </soap:Body>"
        "</soap:Envelope>");
}

QByteArray testWSDiscoveryClient::formatXml(const QByteArray& original)
{
    QByteArray xmlOut;

    QXmlStreamReader reader(original);
    QXmlStreamWriter writer(&xmlOut);
    writer.setAutoFormatting(true);

    while (!reader.atEnd()) {
        reader.readNext();
        if (!reader.isWhitespace()) {
            writer.writeCurrentToken(reader);
        }
    }

    return xmlOut;
}

QByteArray testWSDiscoveryClient::zeroOutUuid(const QByteArray& original)
{
    QString originalString = original;
    originalString.replace(QRegExp("[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}"), "00000000-0000-0000-0000-000000000000");
    return originalString.toLatin1();
}

QTEST_MAIN(testWSDiscoveryClient)

#include "test_wsdiscoveryclient.moc"
