package com.google.i18n.addressinput.common;

/**
 * Abstracted low-level network request API. Implementations making real network requests should
 * attempt to redirect and retry as necessary such that any failure can be considered definitive, as
 * the users of this interface will never retry failed requests.
 */
public interface AsyncRequestApi {
  /**
   * Requests JSON metadata from the given URL and invokes the appropriate methods in the given
   * callback. If the given callback is null, the asynchronous request is still made but no callback
   * methods are invoked. If the given timeout is exceeded then the implementation should, where
   * feasible, attempt to cancel the in-progress network request, but must always invoke the
   * {@link AsyncCallback#onFailure()} callback a short, bounded time after the timeout occurred.
   *
   * @param url the complete URL for the request
   * @param callback the optional callback to be invoked when the request is complete
   * @param timeoutMillis the timeout for the request in milliseconds
   */
  void requestObject(String url, AsyncCallback callback, int timeoutMillis);

  /**
   * Callback API for network requests. One of the methods in this API will be invoked by the
   * {@link AsyncRequestApi} implementation once the network request is complete or has timed out.
   */
  public interface AsyncCallback {
    /** Invoked with the parsed JsoMap from the successful request. */
    public void onSuccess(JsoMap result);

    /** Invoked when a request has definitely failed (after possible retries, redirection ...). */
    public void onFailure();
  }
}
