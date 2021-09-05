<template>
  <div class="page-footer" v-if='footer.actor'>
    <ul class="inner">
      <li v-if="footer.createUpdate">
        Copyright &copy; {{ footer.createYear }}-{{ new Date().getFullYear() }}
        <a v-if="footer.actorLink" :href="footer.actorLink" target="_blank" rel="noopener noreferrer"> {{ footer.actor }} </a> and Contributors. All rights reserved.
      </li>
      <li v-else-if="footer.createYear">
        Copyright &copy; {{ footer.createYear }} <a v-if="footer.actorLink" :href="footer.actorLink" target="_blank" rel="noopener noreferrer"> {{ footer.actor }} </a> and Contributors. All rights reserved.
      </li>
      <li v-else-if="footer.actorLink">
        Copyright &copy; <a v-if="footer.actorLink" :href="footer.actorLink" target="_blank" rel="noopener noreferrer"> {{ footer.actor }} </a> and Contributors. All rights reserved.
      </li>
      <li v-else-if="footer.actor">
        Copyright &copy; {{ footer.actor }} and Contributors. All rights reserved.
      </li>
      <li v-if="footer.licensedLink">
        <a :href="footer.licensedLink" target="_blank" rel="noopener noreferrer">{{ footer.licensed }}</a> Licensed
      </li>
      <li v-for="copyright in footer.copyright" :key="copyright.link">
        <a v-if="copyright.link" :href="copyright.link" target="_blank" rel="noopener noreferrer">{{ copyright.text }}</a>
        <template v-else><span v-html="copyright.text">{{ copyright.text }}</span></template>
      </li>
    </ul>
  </div>
</template>
<script>
export default {
  computed: {
    footer() {
      return this.$themeConfig.footer || this.$themeLocaleConfig.footer || this.$site.themeConfig.footer || {}
    }
  }
};
</script>
<style lang="stylus">
@require '../styles/wrapper.styl'
.page-footer
  @extend $wrapper
  padding 0 2.5rem
  .inner
    border-top 1px solid $borderColor
    padding-top 2rem
    text-align center
    margin 0
    li
      display inline-block
      padding 0 10px
      border-right 1px solid #ccc
      color $textColor
      font-size 12px
      &:first-child
        padding-left 0
      &:last-child
        border-right none
        padding-right 0
@media (max-width: $MQMobileNarrow)
  .page-footer
    padding 0 1.5rem
    .inner
      li
        display block
        border none
        padding 0
        line-height 1rem
</style>
