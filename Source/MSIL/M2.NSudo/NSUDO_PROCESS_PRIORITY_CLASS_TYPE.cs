namespace M2.NSudo
{
    /// <summary>
    /// Contains values that specify the type of process priority class.
    /// </summary>
    public enum NSUDO_PROCESS_PRIORITY_CLASS_TYPE
    {
#pragma warning disable CS1591
        IDLE,
        BELOW_NORMAL,
        NORMAL,
        ABOVE_NORMAL,
        HIGH,
        REALTIME,
#pragma warning restore CS1591
    }
}
