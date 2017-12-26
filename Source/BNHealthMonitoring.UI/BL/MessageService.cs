using System.Reactive;
using System.Reactive.Subjects;
using System.Text;
using HealthMonitoringMessages;
using NetMQ; 
using NetMQ.Sockets;

namespace BNHealthMonitoring.UI.BL
{
    public class MessageService
    {
        private readonly ResponseSocket m_socket;
        private readonly NetMQContext m_context;
        private readonly Poller m_poller;
        private static MessageService s_messageService;
        private ISubject<Unit> m_componentsUpdated = new Subject<Unit>();

        private MessageService()
        {
            m_context = NetMQContext.Create();
            m_socket = m_context.CreateResponseSocket();

            m_poller = new Poller(m_socket);
            m_socket.ReceiveReady += onMessageReceived;
            m_poller.PollTillCancelledNonBlocking();

            m_socket.Bind("tcp://127.0.0.1:49991");
          //  m_socket.Subscribe("", Encoding.ASCII);
        }

        private void onMessageReceived(object p_sender, NetMQSocketEventArgs p_e)
        {
            var msg = Dummy.ParseFrom(p_e.Socket.ReceiveFrameBytes());
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