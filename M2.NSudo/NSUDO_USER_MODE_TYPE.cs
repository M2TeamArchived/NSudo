namespace M2.NSudo
{
    /// <summary>
    /// Contains values that specify the type of user mode.
    /// </summary>
    public enum NSUDO_USER_MODE_TYPE
    {
#pragma warning disable CS1591
        DEFAULT,
        TRUSTED_INSTALLER,
        SYSTEM,
        CURRENT_USER,
        CURRENT_PROCESS,
        CURRENT_PROCESS_DROP_RIGHT
#pragma warning restore CS1591
    }
}
