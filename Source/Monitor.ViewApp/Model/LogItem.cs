namespace Monitor.ViewApp.Model
{
    /// <summary>
    ///     LogItem class stores a single log message.
    /// </summary>
    public class LogItem
    {
        #region Public Properties

        public string Message { get; set; }
        public string Sender { get; set; }

        #endregion
    }
}