namespace Monitor.ViewApp.Model
{
    /// <summary>
    ///     LogItem class stores a single log message.
    /// </summary>
    public class LogItem
    {
        #region Public Properties

        /// <summary>
        /// Gets or sets the message.
        /// </summary>
        public string Message { get; set; }

        /// <summary>
        /// Gets or sets the sender.
        /// </summary>
        public string Sender { get; set; }

        #endregion
    }
}