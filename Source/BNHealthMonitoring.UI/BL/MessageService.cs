using System.Reactive;
using System.Reactive.Subjects;
using NetMQ; 
using NetMQ.Sockets;

namespace BNHealthMonitoring.UI.BL
{
    public class MessageService
    {
        private readonly ResponseSocket m_socket;
        private readonly NetMQPoller m_poller;
        private static MessageService s_messageService;
        private ISubject<Unit> m_componentsUpdated = new Subject<Unit>();

        private MessageService()
        {
            //m_socket = new ResponseSocket();
            //m_socket.ReceiveReady += onMessageReceived;

            //m_poller = new NetMQPoller {m_socket};
            //m_poller.Run();

            //m_socket.Bind("tcp://*:49991");
        }

        private void onMessageReceived(object p_sender, NetMQSocketEventArgs p_e)
        {
            var msg = p_e.Socket.ReceiveFrameBytes();
        }

        public static MessageService GetInsatnce()
        {
            if (s_messageService == null)
                s_messageService = new MessageService();

            return s_messageService;
        }

        public ISubject<Unit> ComponentsUpdate
        {
            get { return m_componentsUpdated; }
        }

    }
}